const http = require('node:http')
const url = require('node:url')
const udp = require('node:dgram')

const cliente_udp = udp.createSocket('udp4')

const server = http.createServer((requisicao, resposta) => {
    const url_tratada = url.parse(requisicao.url)

    if (url_tratada.pathname === "/comando") {
        const comando = url_tratada.query.split("=")[1]

        cliente_udp.send(comando, 12340, "192.168.15.3")
        resposta.end()
    }
})

server.listen(8080, "", null, () => console.log("servidor online!"))

