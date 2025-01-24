# Turing Tutor

Dit project is ontwikkeld als onderdeel van de cursus Machines en Berekenbaarheid. Het doel is een geavanceerde multi-tape Turing Machine (MTM) te bouwen die rekenkundige bewerkingen kan uitvoeren, inclusief optellen, aftrekken, vermenigvuldigen, machtsverheffen, en het verwerken van expressies met haakjes. Het systeem combineert theoretische kennis over automaten met praktische toepassingen en biedt zowel functionele als educatieve waarde.

---

## Functionaliteiten
- Ondersteuning voor de volgende rekenkundige bewerkingen:
    - Optellen en aftrekken
    - Vermenigvuldigen
    - Machtsverheffen
    - Modulo-operaties
    - Haakjes en expressieprioriteit
- GUI ontwikkeld in Qt 5.
- Visuele simulatie van de Turing Machine-operaties.
- Validatie van invoerexpressies met een Earley-parser.
- Logs in HTML die berekeningsstappen weergeven.

---

## Educatieve Waarde
1. **Voor jongere leerlingen**:
  - Het project biedt een interactieve manier om rekenkunde te begrijpen, waarbij berekeningen stap-voor-stap worden weergegeven.
  - Stimuleert logisch denken en vertrouwen in wiskundig redeneren.

2. **Voor informaticastudenten**:
  - Praktische toepassing van theoretische concepten zoals Context-Free Grammar, Earley-parsers, en Turing Machines.
  - Visuele simulatie van complexe computaties helpt bij diepgaand begrip van automatenconcepten.

---

## Teamleden
Ons team bestaat uit de volgende leden, inclusief hun rollen en contactgegevens:

| Naam                  | Rol                                                        | Contact                                                                                          |
|-----------------------|------------------------------------------------------------|--------------------------------------------------------------------------------------------------|
| **Cain Hertoghs**     | Validatie van expressies, compatibiliteit tussen code, implementatie van MTM. | [cain.hertoghs@student.uantwerpen.be](mailto:cain.hertoghs@student.uantwerpen.be)                |
| **Emir Murat**        | Vermenigvuldigen en machtsverheffen met MTM, logs in HTML.  | [emir.murat@student.uantwerpen.be](mailto:emir.murat@student.uantwerpen.be)                      |
| **Jonathan van der Sluijs** | Modulo-operaties, validatie met Earley-parser.             | [jonathan.vandersluijs@student.uantwerpen.be](mailto:jonathan.vandersluijs@student.uantwerpen.be) |
| **Mathis De Herdt**   | GUI in Qt, optellen en aftrekken met MTM, logs in HTML.    | [mathis.deherdt@student.uantwerpen.be](mailto:mathis.deherdt@student.uantwerpen.be)              |


## Installatie
Om dit project te draaien, moet Qt 5 geïnstalleerd zijn. Volg de instructies hieronder:

1. Download en installeer Qt 5 via de officiële website: [Qt Download](https://www.qt.io/download).
2. Zorg ervoor dat de `qmake` tool beschikbaar is via de terminal of command prompt.
3. Clone deze repository naar je lokale machine:
   ```bash
   git clone git@github.com:JonathanSluijs/MB_TOg_groepje10.git
   
## To Do

### Fase 1 deadline: 07/12/2024
- [x] Jonathan: modulo operations
- [x] Jonathan: Implent MTM

- [x] Cain: Brackets and precedence of expressions
- [x] Cain: power operations


- [x] Emir: expression valdiation met earley
- [X] Emir: multiplication


- [X] Mathis: addition and substraction
- [X] Mathis: Implementeren ParserTests met CNFinputTestFiles


### Fase 2 : DEADLINE 17/12/2024
- [x] Cain: Aanpassen expression calculator naar MTM gebruiken en naar logs schrijven
- [X] Cain: Link HTML file to GUI
- [x] Emir: Calculation steps + file interface in QT
- [X] Mathis: Logs in HTML
- [X] Mathis: MTM to Logger
- [X] Mathis & Jonathan: STM to Logger
- [X] Jonathan: MTM to one tape TM 


### Last Fase: 23/12/2024 om 20:00
- PRESENTATION:
- [X] Cain: General explanation
- [X] Emir: Earley parser, CYK (CNF, CFG)
- [X] Cain: Expression Calculator
- [X] Mathis: MTM in general
- [X] Jonathan: Single tape transformer
- [X] Emir: Tests vermelden voor consistentie
- [X] Mathis: DEMO: Output explenation (DEMO)
- [X] Cain: Benefits to society
- [X] Janathan: Project Planning and Motivation



