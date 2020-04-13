import socket #importa modulo socket
 
TCP_IP = '192.168.0.106' # endereço IP do servidor
TCP_PORTA = 31844       # porta disponibilizada pelo servidor
TAMANHO_BUFFER = 1024     # definição do tamanho do buffer
 
# Criação de socket TCP
# SOCK_STREAM, indica que será TCP.
servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# IP e porta que o servidor deve aguardar a conexão
servidor.bind((TCP_IP, TCP_PORTA))
print(TCP_IP, TCP_PORTA)
#Define o limite de conexões. 
servidor.listen(1)
MENSAGEM = "Salve clientela"
print("Servidor dispoivel na porta 5005 e escutando.....") 

# Aceita conexão 
conn, addr = servidor.accept()
print ('Endereço conectado:', addr)

while True:
    #dados retidados da mensagem recebida
    data = conn.recv(TAMANHO_BUFFER)


    if data:
        print ("Mensagem recebida: ", data.decode('UTF-8'))
        
        MENSAGEM = input("Digite ummensagem para o cliente: ")
        conn.send(MENSAGEM.encode())  # envia dados recebidos em letra maiuscula 

        if MENSAGEM == "QUIT":
            servidor.close()
    


