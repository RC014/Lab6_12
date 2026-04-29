# Diagrame Mermaid - Lab 6

Acest fișier conține cod Mermaid pentru:
- schema bloc FSM
- flowchart de execuție

pentru fiecare sarcină: `app_lab_6_1` și `app_lab_6_2`.

## Sarcina 1 - `app_lab_6_1` (LED + buton)

### FSM

```mermaid
stateDiagram-v2
    [*] --> OFF
    OFF: LED stins
    ON: LED aprins

    OFF --> ON: Apăsare validă buton (debounce)
    ON --> OFF: Apăsare validă buton (debounce)
```

### FlowChart

```mermaid
flowchart TD
    A[Start setup] --> B[Init Serial STDIO]
    B --> C[Init Button cu debounce]
    C --> D[Init LED]
    D --> E[Set state OFF]
    E --> F[Print stare initiala]
    F --> G[Loop periodic]

    G --> H{Buton apăsat valid?}
    H -- Nu --> G
    H -- Da --> I[Toggle stare FSM OFF/ON]
    I --> J[Actualizează LED]
    J --> K[printf stare curentă]
    K --> G
```

## Sarcina 2 - `app_lab_6_2` (Semafor inteligent)

### FSM (intersecție globală)

```mermaid
stateDiagram-v2
    [*] --> EW_GREEN

    EW_GREEN: EW=VERDE, NS=ROSU
    EW_YELLOW: EW=GALBEN, NS=ROSU
    NS_GREEN: NS=VERDE, EW=ROSU
    NS_YELLOW: NS=GALBEN, EW=ROSU

    EW_GREEN --> EW_GREEN: Fără cerere NS
    EW_GREEN --> EW_YELLOW: Cerere NS activă și timp EW verde expiră
    EW_YELLOW --> NS_GREEN: După TL_YELLOW_MS
    NS_GREEN --> NS_YELLOW: După TL_NS_GREEN_MS
    NS_YELLOW --> EW_GREEN: După TL_YELLOW_MS
```

### FlowChart

```mermaid
flowchart TD
    A[Start setup] --> B[Init Serial STDIO]
    B --> C[Init pinii semafor EW + NS]
    C --> D[Init buton cerere NS cu debounce]
    D --> E[Set stare initială EW=GREEN NS=RED]
    E --> F[Print stare initială]
    F --> G[Loop periodic cu vTaskDelayUntil]

    G --> H{Eveniment buton NS?}
    H -- Da --> I[Set nsRequestActive = true]
    H -- Nu --> J{Stare curentă?}
    I --> J

    J -- EW_GREEN --> K{Cerere NS activă și TL_EW_GREEN_MS expirat?}
    K -- Nu --> G
    K -- Da --> L[EW->YELLOW; delay TL_YELLOW_MS]
    L --> M[EW->RED; NS->GREEN]
    M --> G

    J -- NS_GREEN --> N{TL_NS_GREEN_MS expirat?}
    N -- Nu --> G
    N -- Da --> O[NS->YELLOW; delay TL_YELLOW_MS]
    O --> P[NS->RED; EW->GREEN]
    P --> Q[Clear nsRequestActive]
    Q --> G
```
