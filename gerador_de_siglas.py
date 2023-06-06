import pyperclip

abrev_siglas = [('IPS', '\\textit{Intelligent Power Switch} (Chave de Potência Inteligente)'),
                ('SJB', '\\textit{Smart Junction Box}'),
                ('CAN', '\\textit{Controller Area Network}'),
                ('PDM', '\\textit{Power Distribution Module} (Módulo de Distribuição de Potência)'),
                ('PWM', '\\textit{Pulse Width Modulation} (Modulação por Largura de Pulso)'),
                ('SEE', 'Sistema Elétrico e Eletrônico'),
                ('ECU', '\\textit{Electronic Control Unit} (Unidade de Comando Eletrônica)'),
                ('ABS', '\\textit{Anti-lock Braking System} (Sistema Antibloqueio de Freio)'),
                ('TCS', '\\textit{Traction Control System} (Sistema de Controle de Tração)'),
                ('ESP', '\\textit{Electronic Stability Program} (Programa Eletrônico de Estabilidade)'),
                ('ACC', '\\textit{Adaptive Cruise Control}'),
                ('SMD', '\\textit{Surface-Mount Device} (Dispositivo de Montagem Superficial)'),
                ('LIN', '\\textit{Local Interconnect Network}'), 
                ('MOST', '\\textit{Media Oriented Systems Transport}'),
                ('USB', '\\textit{Universal Serial Bus} (Porta Serial Universal)'),
                ('SPI', '\\textit{Serial Peripheral Interface}'),
                ('CI', 'Circuito Integrado'),
                ('MOSFET', '\\textit{Metal Oxide Semiconductor Field Effect Transistor} (transistor de efeito de campo metal-óxido-semicondutor)'),
                ('AUTOSAR', '\\textit{AUTomotive Open System ARchitecture}'),
                ('PCI', 'Placa de Circuito Impresso')
                ]

def ordem_alfalbetica():
    abrev_siglas.sort()
    r_string = ''
    for abrev, palavra in abrev_siglas:
        r_string = r_string + f'\t\\item[{abrev}] {palavra}\n'
    print(r_string)
    pyperclip.copy(r_string)


if __name__ == '__main__':
    ordem_alfalbetica()


