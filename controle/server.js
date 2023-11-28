const http = require('node:http')
const url = require('node:url')
const udp = require('node:dgram')

const cliente_udp = udp.createSocket('udp4')

http.createServer((req, res) => {
    const url_tratada = url.parse(req.url)

    if (url_tratada.pathname === "/comando") {
        const { query } = url_tratada

        const comando = Buffer.from(query.split("=")[1])
		console.log(String(comando))
		
		cliente_udp.send(comando, 0, comando.length, 12340, "192.168.15.3", (err) => console.log(err))
		
		res.end()
    }
}).listen(8080, "", null, () => console.log("servidor online!"))

