# Trial

################ STATE MACHINE CODE AND LOGIC ##################

Ova verzija implementira razlicita stanja u toku igre. Cilj je da se igrica odvija kroz tri glavna stanja:
   - stanje main menija
   - stanje galerije
   - play stanje (actual game)
   
Main funkcija koristi klase MainState, GalleryState i kako god ce se zvati klasa za game state.

Pocinje se od MainState objekta, koji predstavlja main menu. 
    Svaka igrica ima game loop, tj beskonacnu while petlju koja se vrti dok je prozor otvoren.
    Ovde svaki state takodje ima svoj loop, iz kog se izlazi i ulazi pod odredjenim uslovima.
        Uslov za izlazak iz main menija je da se izabere jedna od stavki sa menija. Izbor stavke Exit poziva window.close() 
        funkciju koja zatvara ceo prozor za igricu.
        Izborom Play izlazi se iz Main statea i ulazi u Game state.
        Izborom Gallery izlazi se iz Main statea i ulazi u Gallery state.
 
 Ovakva logika treba da se primeni za svako stanje. Ono sto odredjuje iz kog stanja se prelazi je indikator, koji reuzma povratne vrednosti funkcija HandleEvents() za svako stanje. Dakle, na osnovu povratne vrednosti ove fukcije main odredjuje u koje se stanje prelazi. 
 
 Ovo nije pravi game engine, za to sam jos uvek glupa, ali olaksava gledanje u kod, otklanjanje bagova i najbitnije, radi...
 
 Note to future self: dont cringe at this, its a first attempt and i dont know better. Thanks.
