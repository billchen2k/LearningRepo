from PIL import Image  # 手动输入验证码
import pytesseract  # 自动识别验证码
from lxml import etree
import sys
import requests
import getpass
import execjs  # 用于加密

# 记录登录信息的 session
s = requests.session()

mainurl = 'https://portal1.ecnu.edu.cn/cas/login?service=http%3A%2F%2Fapplicationnewjw.ecnu.edu.cn%2Feams%2Fhome.action'
headers = {
	'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36',
	'Refer': 'https://portal1.ecnu.edu.cn/cas/login?service=http%3A%2F%2Fapplicationnewjw.ecnu.edu.cn%2Feams%2Fhome.action%3Bjs'}


def GetRSA(username, password):
	# 获取 des.js 里的内容
	jsstr = requests.get('https://portal1.ecnu.edu.cn/cas/comm/js/des.js').text
	desJS = execjs.compile(jsstr)
	# 调用 strEnc 函数实现 rsa 加密
	try:
		rsa = desJS.call('strEnc', username + password, '1', '2', '3')
	except:
		print('加密错误。')
	return rsa


def GetCode():
	"发送一次新的 get 请求并获取验证码，让用户填写。"
	print('正在获取验证码...')
	r = s.get(mainurl, headers=headers)
	imgraw = s.get('https://portal1.ecnu.edu.cn/cas/code')
	with open(sys.path[0] + '/temp.jpg', 'wb+') as f:
		f.write(imgraw.content)
	# OpenFile(sys.path[0] + '/data/temp.jpg')
	# captacha = input('请输入验证码：')
	print('正在识别验证码...')
	img = Image.open(sys.path[0] + '/temp.jpg')
	captacha = pytesseract.image_to_string(img)
	print('识别结果： {}'.format(captacha))
	return captacha


def ECNULogin(username='', password='', ifEnterPassword=False):
	"""
	返回值：
	0 - 成功登陆
	1 - 验证码错误
	2 - 密码错误
	3 - 未知错误
	"""
	if (ifEnterPassword == True):
		username = input('请输入你的公共数据用户名（学号）：')
		password = getpass.getpass('请输入你的公共数据库密码（直接输入即可，已关闭输入回显）：')
	code = GetCode()

	# 用户名和密码经过了 RSA 加密。
	postData = {
		'code': code,
		'rsa': GetRSA(username, password),
		'ul': len(username),
		'pl': len(password),
		'lt': 'LT-211100-OG7kcGcBAxSpyGub3FC9LU6BtINhGg-cas',
		'execution': 'e1s1',
		'_eventId': 'submit'
	}
	print('正在尝试登录...')
	r = s.post(mainurl, data=postData)
	elements = etree.HTML(r.content)
	errors = elements.xpath('//*[@id="errormsg"]')
	if len(errors) == 0:
		realName = elements.xpath('//a[contains(@title, "查看登录记录")]/font/text()')[0]
		print('登录成功:', realName)
		return 0
	elif elements.xpath('//*[@id="errormsg"]/text()')[0] == "验证码有误":
		return 1
	elif elements.xpath('//*[@id="errormsg"]/text()')[0] == "用户名密码错误":
		return 2
	else:
		error_text = elements.xpath('//*[@id="errormsg"]/text()')[0]
		print(error_text)
		return 3


def main():
	username = input('请输入你的公共数据用户名（学号）：')
	password = getpass.getpass('请输入你的公共数据库密码（直接输入即可，已关闭输入显示）：')
	feedback = ECNULogin(username, password, ifEnterPassword=False)
	while feedback != 0:
		if feedback == 1:
			print('验证码识别错误，请重试。')
			feedback = ECNULogin(username, password, ifEnterPassword=False)
		elif feedback == 2:
			print('用户名或密码错误，请重试。')
			feedback = ECNULogin(ifEnterPassword=True)
		else:
			print('未知错误，输入 0 以重试，输入其他任何内容退出。')
			c = input()
			if (c == '0'):
				feedback = ECNULogin(ifEnterPassword=True)
			else:
				print('无法连接。')


main()
