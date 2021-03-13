# Hotellihuoneen varausohjelma

Valtteri Huuskonen - 2020 syksy - 5G00EI63-3003 C++-ohjelmoinnin perusteet - harjoitustyö

```
 /\   /\__ _ _ __ __ _  __ _                            
 \ \ / / _` | '__/ _` |/ _` |                           
  \ V / (_| | | | (_| | (_| |                           
   \_/ \__,_|_|  \__,_|\__,_| 
  _           _       _ _ _ _                            
 | |__   ___ | |_ ___| | (_) |__  _   _  ___  _ __   ___ 
 | '_ \ / _ \| __/ _ \ | | | '_ \| | | |/ _ \| '_ \ / _ \
 | | | | (_) | ||  __/ | | | | | | |_| | (_) | | | |  __/
 |_| |_|\___/ \__\___|_|_|_|_| |_|\__,_|\___/|_| |_|\___| 
```

## Ominaisuudet ja toiminta

- Ohjelman koodin alussa olevat vakiot asetusten muuttamista varten: 
    - Huoneiden hintaa voi säätää haluamakseen. Esim yhdenhengenhuone yöltä 75€ ja kahdenhengenhuone 130€.
    - Huoneiden lukumäärän ylä- ja alarajan määrää voi muuttaa. (Alkupuolisko silti yhdenhengenhuoneita ja loput kahden hengenhuoneita)
    - Salasana huoneiden varaajien tietojen tulostamiseen.
- Tyylikäs "Varaa hotellihuone" ASCII art
- Ohjelma kertoo vapaiden huoneiden määrän, erotellen huoneet yhden- ja kahdenhengen huoneisiin. 
- Huoneen koon valitseminen 
- Etu- ja sukunimen keräys (myös moniosaiset nimet)
- Huoneen koon vaihto ehdotus, jos pyydetty huonekoko loppu, mutta toista huonekokoa on vielä vapaana
- Ohjelma ilmoittaa vapaan huoneen numeron
- Keston valitseminen öiden lukumäärän mukaan
- Ohjelma kertoo varauksen hinnan, joka riippuu huoneen koosta ja varauksen kestosta
    - Jos tulee sattumalta alennusta, niin alennuksen suuruus ja syy kerrotaan, sekä uusi, alennettu hinta. 
- Yhteenveto, jossa varaajan etu- ja sukunimi, varatun huoneen numero, varauksen kesto, ja lopullinen hinta mahdollisten alennusten jälkeen. 
- Huoneiden varaamista voi jatkaa niin kauan kuin haluaa, kunhan huoneita riittää.  
- Huoneiden tietojen tulostus listana
    - vaatii salasanan (joka muuten on `Hunter2`)
    - pelkistä varatuista huoneista tulostetaan tiedot /tyhjistä näkyy pelkkä huoneen numero)
        - Listan tiedot ovat:
            - Etunimi
            - Sukunimi
            - Huoneen varaus aika (käyttäjän päivämäärä- ja aika-asetusten mukaan)
            - Huoneen varaus aika UNIX epochista sekunteina
            - Varauksen kesto öiden lukumääränä
            - Huoneen koko (1 vai 2 henkeä)
            - Normaali hinta
            - Maksettava hinta (mahdollisen alennuksen jälkeen)
            - Alennusprosentti
- Syötteentarkistus kaikissa inputeissa
    - Ohjelma kertoo missä vika, jos syöte ei ole luku, luku on väärän etumerkkinen tai luku on halutun alueen ulkopuolella.
    - Yes/No kysymyksiin hyväksyy useamman vastausvaihtoehdon: "Y" tai "y" tai "Yes" tai "yes" ovat myönteisiä vastauksia ja muut ovat kielteisiä. Voit siis vastata "Poistu nyt perkele" ja ohjelma tulkkaa vastauksesi kielteisenä. 
    - Ohjelma ei ole rasistinen nimiä kohtaan, vaan nimiin hyväksytään ihan kaikki merkit; esim emojit tai Elon Muskin lapsen nimi "X Æ A-12 Musk" toimii mainiosti. 

## Demo

[![asciicast](https://asciinema.org/a/hprveNRJAyTsFqYDkAZxluTn7.svg)](https://asciinema.org/a/hprveNRJAyTsFqYDkAZxluTn7)

^[https://asciinema.org/a/hprveNRJAyTsFqYDkAZxluTn7](https://asciinema.org/a/hprveNRJAyTsFqYDkAZxluTn7)
