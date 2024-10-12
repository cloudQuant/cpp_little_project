import requests
res = requests.get("http://0.0.0.0:18080/api/contracts")
content = res.text
print("content", content)