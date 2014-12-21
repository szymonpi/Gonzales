__author__ = 'bartek'
from optparse import OptionParser

class Options:

    @staticmethod
    def validate_options(options):
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

    @staticmethod
    def get_options():
        parser = OptionParser()
        parser.add_option("-p", "--platform", dest="platform",
                          help="specify platforms", default="WIN")
        parser.add_option("-n", "--binary_name", dest="binary_name",
                          help="specify binary name", default="default_binary_name")
        parser.add_option("-v", "--verbose",
                  action="store_true", dest="verbose", default=False,
                  help="print status messages to stdout")
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