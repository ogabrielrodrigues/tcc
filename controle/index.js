const comandos = {
    frente: 'ArrowUp',
    re: 'ArrowDown',
    direita: 'ArrowRight',
    esquerda: 'ArrowLeft'
}

const comandos_enviados = []

function enviar(comando) {
    fetch(`http://localhost:8080/comando?comando=${comando}`, {
        method: 'GET'
    })
}

function time() {
    const data = new Date()
    return `${data.getHours()}:${String(data.getMinutes()).padStart(2, '0')}:${String(data.getSeconds()).padStart(2, '0')}`
}

function registrarComando(comando) {
    const cmd = document.createElement('li')
    cmd.innerText = `${time()} /// ${comando}`
    document.querySelector('#cmds').appendChild(cmd)
}

document.documentElement.addEventListener('keyup', (e) => {
    switch (e.key) {
        case comandos.frente:
            enviar("frente")
            registrarComando("frente")
            console.log("frente")
        break
        case comandos.re:
            enviar("re")
            registrarComando("re")
            console.log("ré")
        break
        case comandos.direita:
            enviar("direita")
            registrarComando("direita")
            console.log("direita")
        break
        case comandos.esquerda:
            enviar("esquerda")
            registrarComando("esquerda")
            console.log("esquerda")
        break
    }
})