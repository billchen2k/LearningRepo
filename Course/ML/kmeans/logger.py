from datetime import datetime
import os

# Logger and colors
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class logger:
    @staticmethod
    def __log(msg, level, color=bcolors.ENDC):
        date = datetime.today().strftime("%Y-%m-%d %H:%M:%S")
        with open("log.log", "a+") as f:
            f.write("<{} {}>: {}\n".format(date, level, msg))
        if os.name == "nt":
            print("<{} {}>: {}".format(date, level, msg))
        else:
            print("<{} {}>: {}".format(date, level, color + bcolors.BOLD + msg + bcolors.ENDC))

    @staticmethod
    def info(msg):
        logger.__log(msg, "INFO", bcolors.OKBLUE)

    @staticmethod
    def warn(msg):
        logger.__log(msg, "WARN", bcolors.HEADER)

    @staticmethod
    def error(msg):
        logger.__log(msg, "ERROR", bcolors.FAIL)
