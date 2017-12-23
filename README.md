# Nexus Earth Christmas tree
This project was an idea I had to brighten up our Christmas tree with a blockchain powered LED string. I am a strong believer in the Nexus Earth project, this is the blockchain of my choice to power my Christmas tree 

## Description
Everytime a new block is generated on the Nexus Earth blockchain a random LED is lid up. On the Nexus blockchain there are 3 channels: Prime, Hash, and Nexus Proof of Stake (nPOS). Each of these channels get a specific color on the tree (RGB).
There are always 5 LED's lid up, the first of those fades out when a new block is added and a new LED is lid up.

## Required Components
```
- LED string (I used a 50 LED string with WS2811 drivers)
- WEMOS D1 Mini Pro
- 5V DC Power supply
- Linux device able to run the Nexus Earth daemon
```
## Setting up the Nexus Daemon
Build Instructions: Ubuntu & Debian

1. First ensure you have build essentials installed:

       sudo apt-get install build-essential
    
2. Install Boost:

       sudo apt-get install libboost-all-dev
    
3. Install Berklee DB:

       sudo apt-get install libdb-dev libdb++-dev
    
4. Install Open SSL:

       sudo apt-get install libssl1.0-dev
    
   * If this fails to install because your linux system still supports 0.X
     versions of openssl use this command:
   
         sudo apt-get install libssl-dev
    
5. Install Mini UPNP:

       sudo apt-get install libminiupnpc-dev

* If you get a failed to build because "-lz" was not found this is due to the
fact that your linux operating system is trying to use a 64 bit version of
zlib. You can solve this by installing the 32 bit version here:

       sudo apt-get install lib32z1-dev

### Build Instructions (Daemon): Ubuntu & Debian

    cd ~
    git clone https://github.com/Nexusoft/Nexus.git Nexus
    cd Nexus
    make -f makefile.unix USE_LLD=1 USE_UPNP=1 RELEASE=1

### Download the latest LLD for the Nexus Blockchain
    Go to www.nexusearth.com and download the latest LLD database (http://nexusearth.com/bootstrap/LLD-Database/recent.zip)
    cd ~
    mkdir .Nexus
    unzip recent.zip in your ~/.Nexus/
    
Execute Nexus (you can add -daemon to run it in the background):
    
    ./nexus -checkblocks=10 -checklevel=0 -rpcuser=INPUTSOMETHING -rpcpassword=INPUTSOMETHING -rpcport=9325 -blocknotify="./parseHash.s
    
You can continuous view the log by executing:
    
    tail -f ~/.Nexus/debug.log
    

    
    

