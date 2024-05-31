#!/usr/bin/python3
import os
import sys
import shutil
import subprocess
import time
import glob

_project_dir_name = "example-frameless"
_project_name = "framelessdemo"
_project_version = "v1.0"
if __name__ == "__main__":
    source_dir = os.getcwd()
    print(source_dir)
    title = f"{_project_name} {_project_version}"
    build_softname = (f"{_project_name}.exe" if os.name == "nt" else f"{_project_name}")
    script = os.path.join(source_dir, "script", "output-package.py")
    linuxdeployqt_path = os.path.join(source_dir, "script", "linuxdeployqt-continuous-x86_64.AppImage")
    if not os.path.isfile(script) or not os.path.exists(script):
        sys.exit(0)
    print(os.name)
    if os.name == "nt":
        if "mingw" in sys.argv[0]:
            _mingw_or_msvc = "win32mingw"
            build_dirname = f"build-{_project_dir_name}-Desktop_Qt_5_15_2_MinGW_32_bit-Release"
        else:
            _mingw_or_msvc = "win32msvc"
            build_dirname = f"build-{_project_dir_name}-Desktop_Qt_5_15_2_MSVC2019_32bit-Release"
    else:
        build_dirname = f"build-{_project_dir_name}-Desktop_Qt_5_15_2_GCC_64bit-Release"
    root_dirpath = os.path.split(source_dir)[0]
    lib_path = os.path.split(root_dirpath)[0]
    if os.path.isdir(os.path.join(lib_path, "lib")):
        lib_path = os.path.join(lib_path, "lib")
    else:
        lib_path = os.path.join(source_dir, "lib")
    build_dirpath = os.path.join(root_dirpath, build_dirname)
    build_softpath = os.path.join(build_dirpath, build_softname)
    if (not os.path.isfile(build_softpath) or not os.path.exists(build_softpath)):
        sys.exit(0)
    package_dirpath = os.path.join(source_dir, "output", _project_name)
    if os.path.isdir(package_dirpath):
        shutil.rmtree(package_dirpath)
    time.sleep(2)
    try:
        os.makedirs(package_dirpath)
    except Exception as e:
        print(str(e))
    time.sleep(1)
    package_softpath = os.path.join(package_dirpath, build_softname)
    shutil.copy(build_softpath, package_softpath)
    os.chdir(package_dirpath)
    if os.name == "nt":
        os.system(r"set PATH=C:\Qt\5.15.2\msvc2019\bin;%PATH%")
        os.system(r"C:\Qt\5.15.2\msvc2019\bin\windeployqt.exe " + package_softpath)
    else:
        # shutil.copy(os.path.join(source_dir,"lib","lib.so.2"),os.path.join(package_dirpath))
        os.system(f"chmod +x {linuxdeployqt_path}")
        os.system(f"""export PATH=/home/m/Qt/5.15.2/gcc_64/bin:$PATH
export LD_LIBRARY_PATH=/home/m/Qt/5.15.2/gcc_64/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=/home/m/Qt/5.15.2/gcc_64/plugins:$QT_PLUGIN_PATH
export QML2_IMPORT_PATH=/home/m/Qt/5.15.2/gcc_64/qml:$QML2_IMPORT_PATH
{linuxdeployqt_path} {package_softpath} -appimage -unsupported-allow-new-glibc -no-translations -no-copy-copyright-files""")
    # os.makedirs(os.path.join(package_dirpath,"bin",))
    if os.name == "nt":
        # shutil.copy(os.path.join(source_dir, "bin", "7z.dll"), os.path.join(package_dirpath, "bin"))
        shutil.copy(glob.glob(os.path.join(lib_path, _mingw_or_msvc, "frameless", "*.dll"))[0], package_dirpath)
    else:
        if not os.path.isdir(os.path.join(package_dirpath, "lib")):
            os.makedirs(os.path.join(package_dirpath, "lib"))
        # shutil.move(os.path.join(package_dirpath,"lib.so.2"),os.path.join(package_dirpath,"lib"))
        # shutil.copy(os.path.join(source_dir, "bin", "7z"), os.path.join(package_dirpath, "bin"))

        with open(os.path.join(source_dir, "resource", "linux.desktop"), "r", encoding="utf8") as f1:
            with open(os.path.join(package_dirpath, f"{_project_name}.desktop"), "w", encoding="utf8") as f2:
                f2.write(f1.read().replace("application", _project_name))
        shutil.copy(os.path.join(source_dir, "resource", "icon", "main.ico"),
                    os.path.join(package_dirpath, f"{_project_name}.ico"))
    _li = []
    if os.name == "nt":
        _li.append(os.path.join(package_dirpath, "translations"))
        _li.append(os.path.join(package_dirpath, "D3Dcompiler_47.dll"))
        _li.append(os.path.join(package_dirpath, "libEGL.dll"))
        _li.append(os.path.join(package_dirpath, "libGLESv2.dll"))
        _li.append(os.path.join(package_dirpath, "opengl32sw.dll"))
        _li.append(os.path.join(package_dirpath, "vc_redist.x86.exe"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qgif.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qicns.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qjpeg.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qtga.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qtiff.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qwbmp.dll"))
        _li.append(os.path.join(package_dirpath, "imageformats", "qwebp.dll"))
    else:
        _li.append(os.path.join(package_dirpath, "AppRun"))
        _li.append(os.path.join(package_dirpath, "default.desktop"))
        _li.append(os.path.join(package_dirpath, "default.png"))
        _li.append(os.path.join(package_dirpath, "lib", "libgdk-3.so.0"))
        _li.append(os.path.join(package_dirpath, "lib", "libgtk-3.so.0"))
        _li.append(os.path.join(package_dirpath, "lib", "libQt5QmlModels.so.5"))
        _li.append(os.path.join(package_dirpath, "lib", "libQt5Quick.so.5"))
        _li.append(os.path.join(package_dirpath, "lib", "libQt5QuickTemplates2.so.5"))
        _li.append(os.path.join(package_dirpath, "lib", "libQt5VirtualKeyboard.so.5"))
    for i in _li:
        if os.path.isfile(i):
            os.remove(i)
        elif os.path.isdir(i):
            shutil.rmtree(i)
    with open(os.path.join(package_dirpath, "version.txt"), "w", encoding="utf8") as f:
        f.write(title)
    print("ok.")
