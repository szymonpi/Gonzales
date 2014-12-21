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

    def output_binary_path(self):
        return  self.options.output_directory + "\\" + self.options.binary_name + ".exe"

    def dlls_directory(self):
        return self.options.qt_sdk_directory + "\\bin"

    def create_subfolders(self, output_libraries_path, output_platforms_path):
        if not os.path.exists(output_platforms_path) or not os.path.isdir(output_platforms_path):
            os.mkdir(output_platforms_path)
        if not os.path.exists(output_libraries_path) or not os.path.isdir(output_libraries_path):
            os.mkdir(output_libraries_path)

    def libraries_to_copy(self, output_libraries_path):
        files_to_copy = dict()
        libraries = os.listdir(self.options.library_path)
        for library in libraries:
            files_to_copy[self.options.library_path + "\\" + library] = output_libraries_path + "\\" + library
        return files_to_copy

    def dlls_to_copy(self, dlls_directory, files_to_copy):
        files_to_copy = dict()
        if self.options.platform is "WIN":
            for dll in self.dlls:
                files_to_copy[dlls_directory + "\\" + dll] = self.options.output_directory + "\\" + dll
        return files_to_copy

    def run(self):

        self.printer.printStart()

        output_zip = self.options.output_directory+"\\" + self.options.binary_name + ".zip"
        output_binary_path = self.output_binary_path()
        dlls_directory = self.dlls_directory()
        platform_dll = "qwindows.dll"

        platforms_dir = "platforms"
        libraries_dir = "libraries"
        output_platforms_path = self.options.output_directory + "\\" + platforms_dir
        output_libraries_path = self.options.output_directory + "\\" + libraries_dir
        input_platform_dll_path = self.options.qt_sdk_directory + "\\plugins\\platforms\\" + platform_dll
        output_platform_dll_path = output_platforms_path + "\\" + platform_dll

        self.create_subfolders(output_libraries_path, output_platforms_path)

        files_to_copy = dict()
        files_to_copy[self.app_binary_path(self.options)] = output_binary_path
        files_to_copy.update(self.dlls_to_copy(dlls_directory, files_to_copy))
        files_to_copy[input_platform_dll_path] = output_platform_dll_path
        files_to_copy.update(self.libraries_to_copy(output_libraries_path))

        self.printer.printCopyStatus()

        for in_path, out_path in files_to_copy.iteritems():
            copyfile(in_path, out_path)

        with ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as myzip:
            for file_to_zip in files_to_copy.values():
                output_target = file_to_zip.replace(self.options.output_directory, "");
                myzip.write(file_to_zip, output_target)
            # myzip.write(output_binary_path, self.options.binary_name)
            #
            # for dll in self.dlls:
            #     myzip.write(self.options.output_directory + "\\" + dll, dll)
            #
            # myzip.write(output_platforms_path + "\\" + platform_dll, platforms_dir + "\\" + platform_dll)
            #
            # for library in libraries:
            #     myzip.write(output_libraries_path + "\\" + library, libraries_dir + "\\" + library)

        self.printer.printZipStatus()


        for value in files_to_copy.itervalues():
            os.remove(value)

        rmtree(output_platforms_path)
        rmtree(output_libraries_path)

        self.printer.printCleanUpStatus()
        self.printer.printEndStatus(output_zip)


def main():
    builder = AppBuilder()
    builder.run()


if __name__ == "__main__":
    main();