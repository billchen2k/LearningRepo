import requests
import json

headers = {'authority': 'signup.live.com',
           'x-ms-apiversion': '2',
           'uaid': '5db0d107f6fd4ab4ab17d5d615834a8e',
           'user-agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36',
           'canary': 'W8w094/PjPHgJWqOmskQGlkR0bC/U//FI4EbiIs3rUgyo5iwg5gb3DhT1XJXhnqySS+yGr9FKt5ZFJ5kRzhdUdMh2okgpt3VTrW4sHkj7mKn7rtHEACKmefeK7OC9LNhM6oEsCLRYE8oXIb1NUY+CGyJn9jN9jizL3Er9k7wHDqq31II6BMdRp+6R0NMo2JAeyYNSkuRVqb7RSmM8Z/CoeAEaCauAayeNFilL4FxpB9IWMMLmNkj1Kbw4iyVyUg3:2:3c',
           'content-type': 'application/x-www-form-urlencoded; charset=UTF-8',
           'hpgid': '200639',
           'accept': 'application/json',
           'tcxt': 'ITc7D60B4X/UO16LxfXH/o5iWOYKjCtcwmi2K13WoVs6PRLbOId/8g2VFgZpxYMAR5Q+Pv/46uyrq1P7oig65T2ogORgkiKMji9bX041/M+ZBi2CKdIVyDmI2sul14gfPeJJByeWkBV1MqGWs3KsX/zlSWa9XDxhp5gS9OSNSGPPIoKMya5XQT93rVJIOb6dshXkI4lknIUC5yoGqM2T6m1WbY8AlOEl/aWwIZxLuGBX8md5cdlzpEUZpO8yWNUFsTicQtZZmftR4eHIPDvQt0anCeeu02BfEgeT9zDVfvrBopnXMUZaQfAVqLw/SF4+3syX7V2mwS7yWzrrK/ZEeBcccOD+hkoRpITW/GUxn1QHpKfZo2KfCg8HWwgXlWXIdY8gBDOHQ0wrHupi2trZvytIR40juNK4mhZRaeHr18XkiJEn/5ipM1QvlN95QAjW2KKAuxkWiVJMh25cXii5Wr8QCz28vm2RG/bcsmQP4MxS7bkbTTLzHU2bbPOA1JTPoYDDiDK8xajkx09OGCoccQ==:2:3',
           'x-requested-with': 'XMLHttpRequest',
            'uiflvr': '1001',
            'scid': '100118',
            'x-ms-apitransport': 'xhr',
            'origin': 'https://signup.live.com',
            'sec-fetch-site': 'same-origin',
            'sec-fetch-mode': 'cors',
            'sec-fetch-dest': 'empty',
            'referer': 'https://signup.live.com/signup?mkt=zh-CN&wreply=https%3a%2f%2foffice.live.com%2fstart%2fOutlook.aspx%3fui%3dzh%252DCN%26rs%3dCN%26s%3d2%26auth%3d1%26nf%3d1&wa=wsignin1.0&lw=1&id=257526&uaid=5db0d107f6fd4ab4ab17d5d615834a8e&lic=1',
            'accept-language': 'en-GB,en;q=0.9,zh-CN;q=0.8,zh;q=0.7,en-US;q=0.6,ja-JP;q=0.5,ja;q=0.4',
            'cookie': 'AADNonce=e0fa90d3-1b81-433a-ac92-bca85836b6d5.637329914337129356; mkt=zh-CN; mkt1=zh-CN; amsc=4jxQz22OyB4ajV2KKkRx7kR4ZwOg4eF41HkvxoxbqJdrdcVIdm96ni8vqiJ+vTI3pt+9I6/YcVcaqLTDg/tOqVIGlptknmOB9NYoC1qSbFvJh1qOFrpqTJOETqPx0jySzB6aIq0Bjv9BXG9UM0WPpFomGGn/8qfbzhwSWeHK4GuiUb2R04O2TwEIiETHF8E1UXOjujE7Rzak2HHmFVtK/ePUGh88IBI8JSM2gxSQPSppLq2A2bV6BPXIjJnsRcCDt5/H3VDufaRw2fyb8k6jvCLhZ4naVWb+JH/PxqvPFus=:2:3c; clrc={%2218488%22%3a[%22d7PFy/1V%22%2c%22+VC+x0R6%22%2c%22FutSZdvn%22]}',
}

data = {"signInName": "AlanChen2@outlook.com", "uaid": "5db0d107f6fd4ab4ab17d5d615834a8e", "includeSuggestions": "true", "uiflvr": 1001, "scid": 100118, "hpgid": 200639}

def isOK (mail):
    data['signInName'] = mail;
    res = requests.post('https://signup.live.com/API/CheckAvailableSigninNames?mkt=zh-CN&wreply=https%3a%2f%2foffice.live.com%2fstart%2fOutlook.aspx%3fui%3dzh%252DCN%26rs%3dCN%26s%3d2%26auth%3d1%26nf%3d1&wa=wsignin1.0&lw=1&id=257526&uaid=5db0d107f6fd4ab4ab17d5d615834a8e&lic=1', data=data, headers=headers)
    print(res.text)
    return json.loads(res.text)['isAvailable']

while 1:
    if isOK(input('Input email: ')) == True:
        print('Yes! It\'s available.')
    else:
        print('Try another one.')


        