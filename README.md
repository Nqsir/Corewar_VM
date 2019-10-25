# Corewar

Projet réalisé en équipe avec Victor STEYAERT ([https://github.com/Nqsir](https://github.com/Nqsir)).

Ce projet demande de realiser un compilateur de code ASM ainsi qu'une machine virtuel pour execution de programme appeler "Champion".

### Usage :

    • ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
    • ./asm monchampion.s

### Principales notions :

    • Algorithmes
    • Rigeur 
    • Organisation 
    • Travail en equipe
    
### Résumé du sujet :


Le projet  Corewar  est un projet  où  il faut utiliser pas mal de  matière  grise pour  démêler  les imbroglios qui plane sur le sujet, si vous ne me  croyez  pas, aller y jeter un coup d'œil  !!.  
  
Votre but ? Écrire  deux programmes en C et un  champion:  
  
- Un  premier nommé  asm  qui prend un fichier source  asm  en paramètres. Une  fois le fichier  vérifier, il le compile en "bytecode" pour  être  charger dans la machine virtuel.  
  
- Un second nommé  corewar  qui prend en  paramètre  des "champions". Une fois les champions chargés en mémoire dans la machine virtuel, ils sont exécuter de manière  séquentielle  jusqu  a  ce que mort sen suive et qu'il ne reste plus qu'un champion vivant.  
  
- Un  champion  écrit  en ASM, ce qui correspond au code source avant compilation, en utilisant les instructions autoriser.  
  
Facile ?  
  
Et  bien on  va voir ça...
