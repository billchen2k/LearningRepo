import requests
import json
import icalendar
import datetime
import uuid
from datetime import datetime, timedelta
from icalendar import Calendar, Event, Alarm

URL = "https://wxpay.xdf.cn/xdf/woxue/interface/getlessonByClassno.do?date=1602238820011&schoolId=2&classCode=GFICIW9810452&studentCode=null&bVIP=falsehttps://wxpay.xdf.cn/xdf/woxue/interface/getlessonByClassno.do?date=1602238820011&schoolId=2&classCode=GFICIW9810452&studentCode=null&bVIP=falsehttps://wxpay.xdf.cn/xdf/woxue/interface/getlessonByClassno.do?date=1602238820011&schoolId=2&classCode=GFICIW9810452&studentCode=null&bVIP=falsehttps://wxpay.xdf.cn/xdf/woxue/interface/getlessonByClassno.do?date=1602238820011&schoolId=2&classCode=GFICIW9810452&studentCode=null&bVIP=false"
REMINDER = 15


rawData = requests.get(URL).json()['data']
cal = Calendar()
cal.add('VERSION', '2.0')
cal.add('X-WR-CALNAME', 'IELETS')
cal.add('X-APPLE-CALENDAR-COLOR', '#540EB9')
cal.add('X-WR-TIMEZONE', 'Asia/Shanghai')

def createEvent(name, location, teacher, start, end):
    global REMINDER
    event = Event()
    
    event.add('UID', str(uuid.uuid4()).upper() + '@Bill.Chen@live.com')
    startDate = datetime.strptime(start, '%Y-%m-%d %H:%M:%S').strftime('%Y%m%dT%H%M%S')
    endDate = datetime.strptime(end, '%Y-%m-%d %H:%M:%S').strftime('%Y%m%dT%H%M%S')
    event.add('DTSTART;TZID=Asia/Shanghai', startDate)
    event.add('DTEND;TZID=Asia/Shanghai', endDate)
    event.add('SUMMARY', name)
    event.add('SEQUENCE', '0')
    event.add('DESCRIPTION', teacher)
    event.add('LOCATION', location)
    alarm = Alarm()
    alarm.add('ACTION', 'DISPLAY')
    alarm.add('DESCRIPTION', '事件提醒')
    alarm.add('TRIGGER', timedelta(minutes=-REMINDER))
    event.add_component(alarm)
    return event

for one in rawData:
    e = createEvent(one['courseName'], one['roomName'], one['teacherName'], one['lessonStartTime'], one['lessonEndTime'])
    cal.add_component(e)

with open('IELETS.ics', 'wb+') as f:
    f.write(cal.to_ical())
