import socket #importa modulo socket

TCP_IP = '192.168.0.106' # endereço IP do servidor
TCP_PORTA = 31844      # porta disponibilizada pelo servidor
TAMANHO_BUFFER = 1024
MENSAGEM = ""

# Criação de socket TCP do cliente
cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conecta ao servidor em IP e porta especifica
cliente.connect((TCP_IP, TCP_PORTA))

while MENSAGEM != "QUIT":
    MENSAGEM = input("Digite sua mensagem para o servidor: ")

    # envia mensagem para servidor
    cliente.send(MENSAGEM.encode('UTF-8'))

    data, addr = cliente.recvfrom(1024)
    msg_do_server = data.decode('UTF-8')
    print("Mensagem recebida: ", msg_do_server)

# fecha conexão com servidor
cliente.close()
