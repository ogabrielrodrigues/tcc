const http = require('node:http')
const url = require('node:url')
const udp = require('node:dgram')

const udp_client = udp.createSocket('udp4')

const server = http.createServer((req, res) => {
    const purl = url.parse(req.url)

    if (purl.pathname === "/comando") {
        const {query} = purl

        const comando = query.split("=")[1]

        udp_client.send(comando, 12340, "192.168.15.3")
    }

    res.end()
})

server.listen(8080, "", null, () => console.log("servidor online!"))

