from copy import copy
import zipfile

__author__ = 'bartek'

from optparse import OptionParser
from shutil import copyfile
from shutil import rmtree
from zipfile import ZipFile
import os

class AppBuilder:
    def __init__(self):
        self.dlls = {"icudt51.dll",
                "icuin51.dll",
                "icuuc51.dll",
                "libstdc++-6.dll",
                "libwinpthread-1.dll",
                "Qt5Core.dll",
                "Qt5Gui.dll",
                "Qt5Widgets.dll"}

    def validate_options(self, options):
        if options.platform is None:
            print("No platform specified!")
            exit(1)
        if options.build_directory is None:
            print ("No build directory specified!")
            exit(1)
        if options.output_directory is None:
            print ("No output directory specified!")
            exit(1)
        if options.platform is "WIN":
            if options.qt_sdk_directory is None:
                print ("No qt sdk directory specified!")
                exit(1)
        if options.library_path is None:
            print("No library path specified")
            exit(1)

    def get_options(self):
        parser = OptionParser()
        parser.add_option("-p", "--platform", dest="platform",
                          help="specify platforms", default="WIN")
        parser.add_option("-b", "--build_directory", dest="build_directory",
                          help="build directory", metavar="FILE")
        parser.add_option("-o", "--output_directory", dest="output_directory",
                          help="output directory", metavar="FILE")
        parser.add_option("-q", "--qt_sdk_directory", dest="qt_sdk_directory",
                          help="output directory", metavar="FILE")
        parser.add_option("-l", "--library_path", dest="library_path",
                  help="output directory", metavar="FILE")
        (options, args) = parser.parse_args()
        return options

    def app_binary_path(self, options):
        app_binary = options.build_directory + "\\GonzalesApp\\release\\GonzalesApp.exe"
        return app_binary

    def run(self):
        print("start...")

        options = self.get_options()
        self.validate_options(options)

        print("options validated")

        output_binary = "Gonzales.exe"
        output_binary_path = options.output_directory + "\\" + output_binary
        output_zip = options.output_directory+"\Gonzales.zip"



        copyfile(self.app_binary_path(options), output_binary_path)

        dlls_directory = options.qt_sdk_directory + "\\bin"
        print(dlls_directory)

        if options.platform is "WIN":
            for dll in self.dlls:
                print(dlls_directory + "\\" + dll)
                print(options.output_directory + "\\" + dll)
                copyfile(dlls_directory + "\\" + dll, options.output_directory + "\\" + dll)


        platform_dll = "qwindows.dll"

        platforms_dir = "platforms"
        libraries_dir = "libraries"
        platforms_path = options.output_directory + "\\" + platforms_dir
        libraries_path = options.output_directory + "\\" + libraries_dir

        if not os.path.exists(platforms_path) or not os.path.isdir(platforms_path):
            os.mkdir(platforms_path)

        if not os.path.exists(libraries_path) or not os.path.isdir(libraries_path):
            os.mkdir(libraries_path)

        copyfile(options.qt_sdk_directory + "\\plugins\\platforms\\" + platform_dll, platforms_path + "\\" + platform_dll)
        libraries = os.listdir(options.library_path)

        for library in libraries:
            copyfile(options.library_path + "\\" + library, libraries_path + "\\" + library)

        print("[APP RELEASE BUILDER] --- All files copied")

        with ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as myzip:
            myzip.write(output_binary_path, output_binary)

            for dll in self.dlls:
                myzip.write(options.output_directory + "\\" + dll, dll)

            myzip.write(platforms_path + "\\" + platform_dll, platforms_dir + "\\" + platform_dll)

            for library in libraries:
                myzip.write(libraries_path + "\\" + library, libraries_dir + "\\" + library)

        print("[APP RELEASE BUILDER] --- All files zipped")

        to_delete_files = self.dlls
        to_delete_files.add(output_binary)

        rmtree(platforms_path)
        rmtree(libraries_path)
        for file in to_delete_files:
            os.remove(options.output_directory + "\\" + file)

        print("[APP RELEASE BUILDER] --- Successfully clean-up")
        print("[APP RELEASE BUILDER] --- zip path : ")
        print(output_zip)





def main():
    builder = AppBuilder()
    builder.run()


if __name__ == "__main__":
    main();