# roguelike_cmd

## 📅 Atualizações de Maio de 2025

### ✅ Funcionalidades Adicionadas

- **🎯 Itens no Jogo**
  - Adicionados **3 novos itens**, incluindo o item especial `goldenapple`.

- **📈 Tela de Scoreboard**
  - Nova tela que exibe a **pontuação dos jogadores** após o término da partida.

- **⚔️ Efeito de Ataque**
  - Implementado efeito visual ao atacar inimigos, melhorando o feedback visual ao jogador.

- **🔊 Sons com Threads**
  - Sons do jogo agora são gerenciados em **threads separadas**, permitindo que o áudio toque sem travar a lógica principal.

- **🏆 Conquistas**
  - Adicionados nomes e descrições para **conquistas desbloqueáveis** durante a jogatina.

### 🛠️ Correções e Melhorias

- **💾 Sistema de Save**
  - Corrigido bug no sistema de salvamento.
  - Agora salva também o **apelido do jogador (nick)**.
  - Processamento de entrada convertido para `String Art`.

- **🖥️ Mensagem de Início**
  - Mensagem de boas-vindas exibida ao iniciar o jogo.

---

**Commits relacionados:**
- `d485147` | adicionamos 3 itens dentre eles goldenapple
- `a3eea9c` | Save fix, Scoreboard Screen, Attack effect
- `f29ae55` | Using Thread to Sounds
- `8dccfee` | Mensagem de inicio do jogo
- `181ef56` | Adding achivements name and description
- `b1dcdc4` | Add Nick to Save and Process Input to String Art


## Links

Instruções do trabalho [link](https://onedrive.live.com/?redeem=aHR0cHM6Ly8xZHJ2Lm1zL2IvYy8xYmIzM2I2ZDE1MGRiOTBiL0VRVnV6cEU1TG5OSnUyZkJCa3JRRTNjQnp5a25GWllRVVJtd0ZWcU9vdW5EbFE%5FZT1CQ1ZBZjc&cid=1BB33B6D150DB90B&id=1BB33B6D150DB90B%21s91ce6e052e394973bb67c1064ad01377&parId=1BB33B6D150DB90B%2141466&o=OneUp).

Codigo de exemplo do professor [link](https://github.com/alexrese/roguelike).

## Estrtutura do projeto
Beta:

```
    /root
    ├── src/            # Código-fonte principal
    │   ├── core/       # Lógica central do jogo (game loop, engine)
    │   ├── entities/   # Classes dos personagens, inimigos, etc.
    │   ├── utils/      # Funções auxiliares
    │   ├── renderer/   # Responsável por desenhar no terminal
    │   ├── main.cpp    # Arquivo principal do jogo
    ├── include/        # Arquivos de cabeçalho (.h)
    ├── assets/         # Arquivos de assets (opcional, ex: mapas)
    ├── tests/          # Testes unitários (se for implementar)
    ├── Makefile        # Arquivo para compilar o projeto
    └── README.md       # Instruções do projeto
```

## Status

Data de inicio: [21/03/2025]

# Creditos

| [Daniel](https://github.com/FishingDonut/)
| [Erick](https://github.com/Erick-Mafra)
| [Rodrigo](https://github.com/RodrigoBurattoRibas)

![GitHub top language](https://img.shields.io/github/languages/top/FishingDonut/roguelike_cmd)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/FishingDonut/roguelike_cmd)
![GitHub last commit](https://img.shields.io/github/last-commit/FishingDonut/roguelike_cmd)
