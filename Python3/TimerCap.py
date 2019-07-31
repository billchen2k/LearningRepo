import schedule
import time
import datetime
import os

FILEDIR = "/Users/billchen/Pictures/TimerCaps"
TIME_LEAP = 10
counter = 0

def cap():
	global counter
	os.system("screencapture " + FILEDIR + "/Screenshot\ " + time.strftime("%Y-%m-%d\ %H.%M.%S", time.localtime(time.time()))+ ".jpg")
	counter = counter + 1
	print(time.strftime("%Y-%m-%d %H.%M.%S", time.localtime(time.time())) + "Screenshots captured. (%d in total)" % counter)

if __name__ == '__main__':
	print("TimerCap by @BillChen2000.\n")
	TIME_LEAP = int(input("Please specify time leap (in seconds): "))
	print("Starting capturing screenshots every " + str(TIME_LEAP) +  " s.")
	print("[control] + [c] to suspend.")
	schedule.every(TIME_LEAP).seconds.do(cap)
	while True:
		schedule.run_pending()
