__author__ = 'Bartosz Piekny'

import zipfile
from Printer import EmptyPrinter, Printer
from Options import Options
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

        self.options = Options.get_options()
        Options.validate_options(self.options)
        if self.options.verbose is True:
            self.printer = Printer()
        else:
            self.printer = EmptyPrinter()



    def app_binary_path(self, options):
        app_binary = options.build_directory
        return app_binary

    def run(self):

        self.printer.printStart()
        output_binary = self.options.binary_name
        output_binary_path = self.options.output_directory + "\\" + output_binary
        output_zip = self.options.output_directory+"\\" + self.options.binary_name + ".zip"
        copyfile(self.app_binary_path(self.options), output_binary_path)

        dlls_directory = self.options.qt_sdk_directory + "\\bin"

        if self.options.platform is "WIN":
            for dll in self.dlls:
                copyfile(dlls_directory + "\\" + dll, self.options.output_directory + "\\" + dll)


        platform_dll = "qwindows.dll"

        platforms_dir = "platforms"
        libraries_dir = "libraries"
        platforms_path = self.options.output_directory + "\\" + platforms_dir
        libraries_path = self.options.output_directory + "\\" + libraries_dir

        if not os.path.exists(platforms_path) or not os.path.isdir(platforms_path):
            os.mkdir(platforms_path)

        if not os.path.exists(libraries_path) or not os.path.isdir(libraries_path):
            os.mkdir(libraries_path)

        copyfile(self.options.qt_sdk_directory + "\\plugins\\platforms\\" + platform_dll, platforms_path + "\\" + platform_dll)
        libraries = os.listdir(self.options.library_path)

        for library in libraries:
            copyfile(self.options.library_path + "\\" + library, libraries_path + "\\" + library)

        self.printer.printCopyStatus()

        with ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as myzip:
            myzip.write(output_binary_path, output_binary)

            for dll in self.dlls:
                myzip.write(self.options.output_directory + "\\" + dll, dll)

            myzip.write(platforms_path + "\\" + platform_dll, platforms_dir + "\\" + platform_dll)

            for library in libraries:
                myzip.write(libraries_path + "\\" + library, libraries_dir + "\\" + library)

        self.printer.printZipStatus()

        to_delete_files = self.dlls
        to_delete_files.add(output_binary)

        rmtree(platforms_path)
        rmtree(libraries_path)
        for file in to_delete_files:
            os.remove(self.options.output_directory + "\\" + file)

        self.printer.printCleanUpStatus()
        self.printer.printEndStatus(output_zip)


def main():
    builder = AppBuilder()
    builder.run()


if __name__ == "__main__":
    main();