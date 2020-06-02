#include <iostream>
#include <cmath>
#include <memory>
#include <vector>

#include <direct.h>
#include <stdio.h>

#include "miniz.h"

#include "player.h"
#include "player_gun.h"
#include "irrlicht/irrlicht_handler.h"
#include "graphics_engine.h"
#include "vec3.h"
#include "box.h"
#include "physics_engine.h"

#define PI std::acos(-1)
#define min(a,b) ((a<b) ? a:b)
#define ZIP_BUF_SIZE 1024*1024

struct BSPLump //Data in BSP files is stored in lumps. This is an entry which describes a lump.
{
    int offset; //Offset from beginning of file
    int length; //Length of the lump. Always a multiple of 4
};

struct BSPHeader
{
    char magic[4]; //The magic "IBSP" signifier
    int version; //should be 46

    BSPLump lumps[17]; //Quake3 has 17 lumps per map
};

struct Node
{
    int plane;
    int children[2];
    int mins[3]; //Minimum bounding box coord
    int maxs[3]; //Maximum bounding box coord
};

struct Leaf
{
    int cluster;
    int area;
    int mins[3];
    int maxs[3];
    int leaf_face;
    int num_leaf_faces;
    int leaf_brush;
    int num_leaf_brushes;
};

struct Brush
{
    int brush_side;
    int num_brush_sides;
    int texture;
};

struct BrushSide
{
    int plane;
    int texture;
};

struct Plane
{
    float normal[3];
    float dist;
};

struct BSPTexture
{
    char name[64];
    int flags;
    int contents;
};

struct Vertex
{
        float position[3];
        float tex_cord[2][2];
        float normal[3];
        unsigned char color[4];
};

struct Face
{
        int texture;
        int effect;
        int type;

        int vertex;
        int num_vertices;

        int mesh_vert;
        int num_mesh_vertices;
        int lm_index;
        int lm_start[2];
        int lm_size[2];
        float lm_origin[3];
        float lm_vecs[2][3];
        float normal[3];
        int size[2];
};

//Determinant of a 3x3 matrix.
//This is used for calculating the vertices of a BSP plane.
class Det3x3
{
    float vals[3][5]; //Extra columns are for cramers rule
public:
    Det3x3(float m[9])
    {
        float mat[3][3];
        int i = 0;
        int x = 0;
        int y = 0;
        while(x<3 && i<9)
        {
            mat[x][y] = m[i];
            i++;
            if(y==2)
            {
                x++;
                y=0;
            }
            else
                y++;
        }
        init(mat);
    }

    void init(float m[3][3])
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                vals[i][j] = m[i][j];
            }
        }
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<2; j++)
            {
                vals[i][j+3] = vals[i][j];
            }
        }
    }

    void print()
    {
        for(int i=0; i<3; i++)
        {
            std::string row = "";
            for(int j=0; j<5; j++)
            {
                row += std::to_string(vals[i][j]) + " ";
            }
            std::cout << row << '\n';
        }
        std::cout << '\n';
        return;
    }

    float get_soln() const //Get solution by using Cramer's rule
    {
        float solution = 0.f;
        float down = (vals[0][0] * vals[1][1] * vals[2][2]) +
            (vals[0][1]*vals[1][2]*vals[2][3])  + (vals[0][2]*vals[1][3]*vals[2][4]);
        float up = (vals[2][0]*vals[1][1]*vals[0][2]) +
            (vals[2][1]*vals[1][2]*vals[0][3]) + (vals[2][2]*vals[1][3]*vals[0][4]);
        solution += (down-up);
        return solution;
    }
};

struct PlaneVert
{
    vec3f vert;
    int planes[3]; //Indices into a plane vec

    PlaneVert(const vec3f &v)
    :vert(v)
    {}
};

bool load_physics_map(PhysicsEngine &physics_engine, std::string map_file_loc, std::string map_name, GraphicsEngine &graphics_engine) //Load physics world from map. REMOVE REFERENCES TO PHYSICS ENGINE AND GRAPHCIS ENGINE AND REPLACE WITH MESSAGING SYSTEM
{
    bool relative = false;
    for(auto it=map_file_loc.begin(); it!=map_file_loc.end(); it++)
    {
        if(*it=='.' && *std::next(it) == '.')
        {
            relative = true;
            break;
        }
    }

    std::string map_full_file_loc;
    if(relative)
    {
        char cwd[FILENAME_MAX];
        _getcwd(cwd, FILENAME_MAX);
        std::cout << cwd << '\n';

        std::string tmp = cwd;
        std::vector<std::string> cwd_vec;
        std::string curr_string = "";
        for(auto it=tmp.begin(); it!=tmp.end(); it++) //Convert cwd string to std::vector
        {
            if(*it != '\\')
                curr_string += *it;
            else//If the current char is \, add string to vec, then clear string
            {
                cwd_vec.push_back(curr_string);
                curr_string = "";
            }
            if(std::next(it) == tmp.end())
                cwd_vec.push_back(curr_string);
        }

        std::vector<std::string> map_full_file_loc_vec;
        curr_string = "";
        for(auto it=map_file_loc.begin(); it!=map_file_loc.end(); it++) //Convert map_file_loc to string
        {
            if(*it=='.' && *std::next(it)=='.') //When '..' is in string, delete the highest cwd level
                cwd_vec.pop_back();
            else if(*it=='/' && curr_string != "")
            {
                map_full_file_loc_vec.push_back(curr_string);
                curr_string = "";
            }
            else if(*it!='/' && *it!='.')
                curr_string += *it;
            else if(*it=='.' && *std::next(it)!='.' && *std::next(it) !='/')
                curr_string += *it;
            if(std::next(it) == map_file_loc.end())
                map_full_file_loc_vec.push_back(curr_string);
        }

        for(auto it=cwd_vec.begin(); it!= cwd_vec.end(); it++)
        {
            map_full_file_loc += *it;
            map_full_file_loc += '/';
        }
        for(auto it=map_full_file_loc_vec.begin(); it!=map_full_file_loc_vec.end(); it++)
        {
            map_full_file_loc += *it;
            if(std::next(it) != map_full_file_loc_vec.end())
                map_full_file_loc += '/';
        }
    }
    else
        map_full_file_loc = map_file_loc;
    std::cout << map_full_file_loc << '\n';

    size_t size;
    void* unzipped = mz_zip_extract_archive_file_to_heap(map_full_file_loc.c_str(), map_name.c_str(), &size,  0);
    if(unzipped == NULL)
    {
        std::cout << "Error unzipping\n";
        return false;
    }

    BSPHeader bsp_header;

    strncpy(bsp_header.magic, (const char*)unzipped, 4);
    const char* z = ((const char*)unzipped)+4;
    bsp_header.version = *(int*)z;
    std::cout << "MAGIC: " << std::string(bsp_header.magic,4) << " Version: " << bsp_header.version << '\n';

    BSPLump* j = (BSPLump*)(z+4);
    for(int i=0; i<17; i++)
    {
        bsp_header.lumps[i] = *j;
        j++;
    }

    const int num_brushes = (bsp_header.lumps[8].length)/sizeof(Brush);
    Brush *brushes = (Brush*)((const char*)unzipped + bsp_header.lumps[8].offset);

    const int num_brush_sides = (bsp_header.lumps[9].length)/sizeof(BrushSide);
    BrushSide *brush_sides = (BrushSide*)((const char*)unzipped + bsp_header.lumps[9].offset);

    const int num_leaves = (bsp_header.lumps[4].length)/sizeof(Leaf);
    Leaf *leaves = (Leaf*)((const char*)unzipped + bsp_header.lumps[4].offset);

    Plane *planes = (Plane*)((const char*)unzipped + bsp_header.lumps[2].offset);

    BSPTexture *textures = (BSPTexture*)((const char*)unzipped + bsp_header.lumps[1].offset);

    const int num_vertices = (bsp_header.lumps[10].length)/sizeof(Vertex);
    Vertex *vertices = (Vertex*)((const char*)unzipped + bsp_header.lumps[10].offset);

    for(int i=0; i<num_leaves; i++)
    {
        Leaf l = *(leaves+i);
        for(int j=0; j<l.num_leaf_brushes; j++)
        {
            Brush b = *(brushes+l.leaf_brush+j);
            BSPTexture t = *(textures+b.texture);
            //This is messy because polygons with more than 10 faces aren't handled.
            //Move to hex instead. Better yet don't use combo
            if(t.contents & 1 && b.num_brush_sides<=9)
            {
                std::vector<Plane> planes_vec;
                for(int s=0; s<b.num_brush_sides; s++)
                {
                    BrushSide bs = *(brush_sides + b.brush_side + s);
                    Plane p = *(planes + bs.plane);
                    planes_vec.push_back(p);
                }
                std::set<std::string> comb;
                for(int x=0; x<b.num_brush_sides; x++)
                {
                    for(int y=0; y<b.num_brush_sides; y++)
                    {
                        for(int z=0; z<b.num_brush_sides; z++)
                        {
                            if(x!=y && x!=z && y!=z)
                            {
                                int n[3] {x,y,z};
                                int low_index = 0;
                                int high_index = 0;
                                int mid_index = 0;
                                for(int l=0;l<3;l++)
                                {
                                    if(n[l]<n[low_index])
                                        low_index = l;
                                    if(n[l]>n[high_index])
                                        high_index = l;
                                }
                                for(int l=0; l<3; l++)
                                {
                                    if(l!= low_index && l!=high_index)
                                        mid_index = l;
                                }
                                std::string c =
                                    std::to_string(n[low_index]) + std::to_string(n[mid_index]) +
                                    std::to_string(n[high_index]);
                                comb.insert(c);
                            }
                        }
                    }
                }

                std::vector<PlaneVert> vertices;
                //Calculate vertices from the BSP planes using plane equation
                for(auto it=comb.begin(); it!=comb.end(); it++)
                {
                    //Convert the combination into ints to access the planes_vec
                    int p1i = (*it)[0] - '0';
                    int p2i = (*it)[1] - '0';
                    int p3i = (*it)[2] - '0';

                    Plane p1 = planes_vec[p1i];
                    Plane p2 = planes_vec[p2i];
                    Plane p3 = planes_vec[p3i];

                    float x1 = p1.normal[0];
                    float x2 = p2.normal[0];
                    float x3 = p3.normal[0];
                    float y1 = p1.normal[1];
                    float y2 = p2.normal[1];
                    float y3 = p3.normal[1];
                    float z1 = p1.normal[2];
                    float z2 = p2.normal[2];
                    float z3 = p3.normal[2];

                    float dist1 = p1.dist;
                    float dist2 = p2.dist;
                    float dist3 = p3.dist;

                    //They planes must intersect if they aren't parallel. Check if parallel
                    bool parallel = false;
                    if((x1/x2 == y1/y2 == z1/z2) || (x2/x3 == y2/y3 == z2/z3))
                    {
                        if(isnan(x1/x2) || isnan(y1/y2) || isnan(z1/z2)
                            || isnan(x2/x3) || isnan(y2/y3) || isnan(z2/z3))
                            parallel = false;
                        else
                            parallel = true;
                    }

                    if(!parallel)
                    {
                        float df[9] = {x1, y1, z1, x2, y2, z2, x3, y3, z3};
                        Det3x3 det(df);
                        float d = det.get_soln();

                        float dfx[9] = {dist1, y1, z1, dist2, y2, z2, dist3, y3, z3};
                        Det3x3 detx(dfx);
                        float dx = detx.get_soln();

                        float dfy[9] = {x1, dist1, z1, x2, dist2, z2, x3, dist3, z3};
                        Det3x3 dety(dfy);
                        float dy = dety.get_soln();

                        float dfz[9] = {x1, y1, dist1, x2, y2, dist2, x3, y3, dist3};
                        Det3x3 detz(dfz);
                        float dz = detz.get_soln();

                        if(dist1 !=0 && dist2 != 0 && dist3 != 0 && d != 0)
                        {
                            vec3f point(dx/d, dy/d, dz/d);
                            PlaneVert v(point);
                            v.planes[0] = p1i; v.planes[1] = p2i; v.planes[2] = p3i;
                            vertices.push_back(v);
                        }
                    }
                }
                //Loop through the planes and find the vertices that belong
                //to the plane.
                for(int p=0; p<planes_vec.size(); p++)
                {
                    std::vector<size_t> p_verts;
                    for(size_t vert=0; vert<vertices.size(); vert++)
                    {
                        int curr_p_vert_num = 0;
                        for(int i=0; i<3; i++)
                        {
                            if(vertices[vert].planes[i] == p)
                                curr_p_vert_num++;
                        }
                        if(curr_p_vert_num == 1)
                        {
                            p_verts.push_back(vert);
                        }
                    }
                    if(p_verts.size()<2) //Can't draw a line with less than 2 vertices
                        continue;
                    //This just draws lines sequentially from vertex to vertex
                    for(auto it=p_verts.begin(); it!=std::prev(p_verts.end()); it++)
                    {
                        graphics_engine.draw_line(vertices[*it].vert*0.015625, vertices[*std::next(it)].vert*0.015625);
                    }
                }
            }
        }
    }

    free(unzipped);

    return true;
}

int main()
{
    //Window variables
    bool b_vsync = true;
    bool b_fullscreen = true;
    unsigned int i_width = 1920;
    unsigned int i_height = 1080;

    IrrlichtHandler irrlicht_handler(b_vsync, b_fullscreen,
        i_width, i_height);
    irrlicht_handler.create_device();

    GraphicsEngine graphics_engine(&irrlicht_handler);
    PhysicsEngine physics_engine;
    bool b_map_loaded = load_physics_map(physics_engine, "../../irrlicht_engine/media/map-20kdm2.pk3", "maps/20kdm2.bsp", graphics_engine);
    if(b_map_loaded)
        std::cout << "Physics map loaded\n";
    else
        std::cout << "Physics map not loaded\n";

    //Load in temp model that comes with Irrlicht
    unsigned int sydney = graphics_engine.load_animated_mesh("../../irrlicht_engine/media/sydney.md2");
    graphics_engine.set_animated_mesh_texture(sydney, "../../irrlicht_engine/media/sydney.bmp");
    graphics_engine.set_animated_mesh_position(sydney, vec3f(1,0,1));

    //Resize Sydney to fit scene scale
    float sydney_scalar = 1/graphics_engine.get_animated_mesh_height(sydney); //Sydney should be one unit tall
    graphics_engine.set_animated_mesh_scale(sydney, vec3f(sydney_scalar,sydney_scalar,sydney_scalar));

    std::cout << "Sydney loaded\n";

    graphics_engine.add_fps_camera(vec3f(0,0,0));

    //Load in gun model
    unsigned int gun_mesh = graphics_engine.load_animated_mesh("../resources/temp_gun/temp_gun.obj");
    graphics_engine.set_animated_mesh_parent_to_fps_camera(gun_mesh);

    std::cout << "Gun loaded\n";

    //These are only temporary. Can be deleted once proper animation for aiming
    //is built.
    vec3f gun_mesh_default_pos(0.05f,-0.05f,0.05f);
    vec3f gun_mesh_default_rot(0,-120,0);
    vec3f gun_mesh_aimed_pos(0,-1,8);
    vec3f gun_mesh_aimed_rot(-60,-90,60);

    float gun_scalar = (0.01f)*graphics_engine.get_animated_mesh_height(gun_mesh);
    graphics_engine.set_animated_mesh_scale(gun_mesh, vec3f(gun_scalar, gun_scalar, gun_scalar));
    graphics_engine.set_animated_mesh_position(gun_mesh, gun_mesh_default_pos);
    graphics_engine.set_animated_mesh_rotation(gun_mesh, gun_mesh_default_rot);

    //Quake3 Level
    /*graphics_engine.load_map_mesh_from_file("../../irrlicht_engine/media/map-20kdm2.pk3", "20kdm2.bsp");
    graphics_engine.set_map_mesh_position(vec3f(-20,-2,-20));
    float map_scalar = 10/graphics_engine.get_map_mesh_height();
    std::cout << "MAP SCALAR: " << map_scalar << '\n'; //0.015625
    graphics_engine.set_map_mesh_scale(vec3f(map_scalar,map_scalar,map_scalar));
    std::cout << "Map loaded\n";*/

    //Box object
    Box box(vec3f(1,0,2), vec3f(0,0,0));
    unsigned int box_mesh = graphics_engine.load_animated_mesh("../resources/temp_box/temp_box.obj");
    graphics_engine.set_animated_mesh_texture(box_mesh, "../resources/temp_box/temp_box.jpg");
    graphics_engine.set_animated_mesh_position(box_mesh, box.get_position());
    graphics_engine.set_animated_mesh_rotation(box_mesh, box.get_rotation());

    float box_scalar = 1/graphics_engine.get_animated_mesh_height(box_mesh);
    graphics_engine.set_animated_mesh_scale(box_mesh, vec3f(box_scalar,box_scalar,box_scalar));

    std::cout << "Box loaded\n";

    Player player(vec3f(0,0,0));
    PlayerGun player_gun;
    bool player_walk = false;

    //Physics Objects
    unsigned int ground_rig_body = physics_engine.create_rigid_body(
        PhysicsShape::BoxShape, vec3f(50,1,50), vec3f(0,-2.5,0), 0
    );
    unsigned int box_rig_body = physics_engine.create_rigid_body(
        PhysicsShape::BoxShape, vec3f(1,1,1), box.get_position(), 100
    );

    unsigned int then = irrlicht_handler.get_time(); //used to calculate time between frames

    while(irrlicht_handler.run()) //Main game loop
    {
        const unsigned int now = irrlicht_handler.get_time();
        const float frame_delta_time = (now-then)/1000.f;

        vec3f player_move_vec(0,0,0); //Indicates which direction player will move

        //User Input
        if(irrlicht_handler.is_key_down(irr::KEY_ESCAPE)) //Close game when ESCAPE pressed
        {
            irrlicht_handler.close_device();
            break;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_W))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = (float)std::sin(rotY*PI/180.f);
            float dz = (float)std::cos(rotY*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x += dx;
            if(!isnan(dz))
                player_move_vec.z += dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_S))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = (float)std::sin(rotY*PI/180.f);
            float dz = (float)std::cos(rotY*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x -= dx;
            if(!isnan(dz))
                player_move_vec.z -= dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_D))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = (float)std::sin((rotY+90)*PI/180.f);
            float dz = (float)std::cos((rotY+90)*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x += dx;
            if(!isnan(dz))
                player_move_vec.z += dz;
            player_walk = true;
        }
        if(irrlicht_handler.is_key_down(irr::KEY_KEY_A))
        {
            const float rotY = irrlicht_handler.get_fps_camera_rotation_y();
            float dx = (float)std::sin((rotY+90)*PI/180.f);
            float dz = (float)std::cos((rotY+90)*PI/180.f);
            if(!isnan(dx))
                player_move_vec.x -= dx;
            if(!isnan(dz))
                player_move_vec.z -= dz;
            player_walk = true;
        }

        if(irrlicht_handler.is_mouse_down(1))
        {
            player_gun.try_aim_change();
        }

        irrlicht_handler.set_fps_camera_position(player.get_position());

        if(player_move_vec.get_magnitude() != 0)
            player.walk(player_move_vec.get_normalized());
        else
            player_walk = false;
        player_move_vec = vec3f(0,0,0);

        if(!player_walk)
            player.stop_walk();
        else
            player_walk = false;

        player.update();
        player_gun.update(frame_delta_time);

        physics_engine.step_simulation(frame_delta_time);
        then = now;
        box.set_position(physics_engine.get_rigid_body_pos(box_rig_body));

        graphics_engine.set_animated_mesh_position(box_mesh, box.get_position());
        graphics_engine.set_animated_mesh_rotation(box_mesh, box.get_rotation());

        //Drawing
        //Why doesn't the graphics engine control this? Maybe move this. -Morgen
        irrlicht_handler.begin_drawing();
        irrlicht_handler.draw_scene();
        irrlicht_handler.draw_gui();
        graphics_engine.draw();
        irrlicht_handler.end_drawing();

    }

    irrlicht_handler.drop_device();

    return 0;
}
