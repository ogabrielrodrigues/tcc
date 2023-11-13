const w = document.querySelector('#key-w')
const a = document.querySelector('#key-a')
const s = document.querySelector('#key-s')
const d = document.querySelector('#key-d')

const comandos = {
    frente: 'ArrowUp',
    re: 'ArrowDown',
    direita: 'ArrowRight',
    esquerda: 'ArrowLeft'
}

const teclas = {
    frente: w,
    re: s,
    direita: d,
    esquerda: a
}

function enviarComando(comando) {
    fetch(`http://localhost:8080/comando?comando=${comando}`, {
        method: 'GET'
    })
}

function limparTeclas() {
    setTimeout(() => {
        teclas.frente.classList.remove("bg-violet-600")
        teclas.re.classList.remove("bg-violet-600")
        teclas.direita.classList.remove("bg-violet-600")
        teclas.esquerda.classList.remove("bg-violet-600")
    }, 200)
}

function destacarTecla(tecla) {
    switch (tecla) {
        case "frente":
            teclas.frente.classList.add("bg-violet-600")
            limparTeclas()
        break
        case "re":
            teclas.re.classList.add("bg-violet-600")
            limparTeclas()
        break
        case "direita":
            teclas.direita.classList.add("bg-violet-600")
            limparTeclas()
        break
        case "esquerda":
            teclas.esquerda.classList.add("bg-violet-600")
            limparTeclas()
        break
    }
}

document.documentElement.addEventListener('keyup', (evento) => {
    switch (evento.key) {
        case comandos.frente:
            enviarComando("frente")
            destacarTecla("frente")
        break
        case comandos.re:
            enviarComando("re")
            destacarTecla("re")
        break
        case comandos.direita:
            enviarComando("direita")
            destacarTecla("direita")
        break
        case comandos.esquerda:
            enviarComando("esquerda")
            destacarTecla("esquerda")
        break
    }
})