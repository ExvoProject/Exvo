## REMOTE MASTERNODE BUILD NOTES

#### System requirements

##### Remote:
An Ubuntu 16.04 64bit server is recommended with at least 768MB
of memory and 10GB space available when running a Masternode.

##### Local:
Windows 7 64 bit or newer, or Ubuntu 16.04 64bit Desktop.
At least 2048MB of memory and 10GB space available for chain data.

________________________________________________________________________________

#### Local Machine

Note that the following steps can be performed via command line using the *exvo-cli*
instead of using the EXVO Qt wallet.

1.  Download latest version of EXVO Qt client for windows or linux

        https://github.com/exvo/exvo/releases

2.  Create exvo.conf file with the following contents:

```
rpcallowip=127.0.0.1
rpcuser=YourUserName
rpcpassword=YourRPCPassword
server=1
daemon=1
listen=1
```

    Place the configuration file in its correction location:

    For Linux: ${HOME}/.exvo/exvo.conf
    For Windows: %appdata%\exvo.conf

3.  Start EXVO Qt gui client and allow the chain to sync

4.  Go to Help --> Debug Window --> Console and enter: `getaccountaddress 0`
    Copy the generated address to a text file.

5.  In the console enter: `masternode genkey`
    Copy the generated private key to a text file.

5.  Send exactly 15,000 STAK in a single transaction to the address generated from Step 4

6.  After you have received the STAK from Step 5, go to Help --> Debug Window --> Console and enter: `masternode outputs`
    
    You should see output similar to below indicating that the node has recognised coins as eligible to be used
    as collateral for a Masternode.

```
{
  "d565175089b0f4dce2294dc003799ae0c9cb703cadd996a0a4224458f176eb6e": "0"
}
```

7.  Shutdown the EXVO Qt wallet

8.  Modify the exvo.conf and add the lines noted here:

```
rpcallowip=127.0.0.1
rpcuser=YourUserName
rpcpassword=YourRPCPassword
server=1
daemon=1
listen=1
# **** add the following new lines ****
maxconnections=256
masternode=1
masternodeprivkey=<your_private_key_generated_in_step_5>
externalip=<external_ip_of_your_remote_node>:8585
promode=1
```

#### Remote Machine

1.  Download latest version of EXVO linux amd64 release

        https://github.com/exvo/exvo/releases
2.  Create exvo.conf file with the following contents:

```
rpcallowip=127.0.0.1
rpcuser=YourUserName
rpcpassword=YourRPCPassword
server=1
daemon=1
listen=1
maxconnections=256
promode=1
```    

3.  Create masternode.conf file in the same directory as your wallet.dat.  The masternode.conf
    format consists of a space seperated text file. Each line consisting of an alias, ip address
    followed by port, masternode private key, collateral output transaction id and collateral
    output index (matching the result of Local Machine Step 6)

```
alias 127.0.0.1:8585 masternode_private_key collateral_output_txid collateral_output_index

e.g.

mn01 127.0.0.1:8585 92bHZcSpmT6UinHzR8VgaVZVgBVfbDRCh1WogXXXXXXtf9pyZ4Y d565175089b0f4dce2294dc003799ae0c9cb703cadd996a0a4224458f176eb6e 0
```

4.  Start EXVO daemon using command `./exvod`; you should get the following output:

```
Missing masternode input, please look at the documentation for instructions on masternode creation
```

5.  Then enter the following command using *exvo-cli*

```
./exvo-cli masternode debug
```

#### Local Machine

1.  Back on your local machine; start the EXVO Qt client

2.  Go to Help --> Debug Window --> Console and enter: `masternode start`
    You should get the following message:

```
successfully started masternode
```

3.  If you then enter: `masternodelist`
    You should be able to locate the externalip of your remote node from the
    output list of masternodes.

    **Congratulations your masternode is up and running!**

    Alternatively, on the EXVO Qt client Masternodes tab --> All Masternodes you should see your
    remote node ip address listed with its public key and other data


3.  You can now shutdown your local "cold" wallet
