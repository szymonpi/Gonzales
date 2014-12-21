__author__ = 'bartek'

class EmptyPrinter:
    def printStart(self):
        pass
    def printCopyStatus(self):
        pass
    def printZipStatus(self):
        pass
    def printCleanUpStatus(self):
        pass
    def printEndStatus(self,output_zip):
        pass

class Printer:
    def printStart(self):
        print("[APP RELEASE BUILDER] Start processing...")

    def printCopyStatus(self):
        print("[APP RELEASE BUILDER] --- All files copied")

    def printZipStatus(self):
        print("[APP RELEASE BUILDER] --- All files zipped")

    def printCleanUpStatus(self):
            print("[APP RELEASE BUILDER] --- Successfully clean-up")

    def printEndStatus(self, output_zip):
            print("[APP RELEASE BUILDER] --- zip path : ")
            print(output_zip)

