import os, sys, time

def IsValidBuildDir(entry):
    if not entry.name.startswith('.') and entry.is_dir() \
        and entry.name != "x64" and entry.name != "CMakeFiles":
        return True
    else:
        return False

def main():
    currDir = os.path.realpath(sys.argv[1])
    subDirEntries = []

    with os.scandir(os.path.join(currDir, "tests")) as it:
        for entry in it:
            if IsValidBuildDir(entry):
                subDirEntries.append(entry)

    while len( subDirEntries ) == 0 :
        print("[-] Tests are yet to be built. Waiting...")
        time.sleep(5)

    execPaths = []
    print("-==RUNNING TEST SCRIPTS!=--")
    for dir in subDirEntries:
        execDir = os.path.join(dir, "Debug")
        with os.scandir(execDir) as it:
            for entry in it:
                if entry.name.endswith(".exe"):
                    execPaths.append(os.path.join(execDir,entry))

    for exec in execPaths:
        print("[-] Running test: ", os.path.split(exec)[1])
        os.system(exec)

if __name__ == '__main__':
    main()
