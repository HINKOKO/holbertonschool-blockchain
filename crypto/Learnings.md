# **General Learnings - Crypto project**

- **1. How a Blockchain is considered “unbreakable”**

For several reasons, That marvellous technology is considered to be <i>Unbreakable</i>... <br>
As the name suggests, a "block"-"chain" is a chain (or list) of blocks. <br>
What's in the blocks Francis ? Well, as usual, like all computer science fields, we deal with some **data**, hence each blocks embed some **data**<br>
Regarding Bitcoin e.g. (and countless other cryptocurrencies), that data will consist of (among other things):

- Previous block's **hash**
- **data** => a list of transactions (that's what we need to corrupt !!)
- Timestamp (UNIX second since January 1st 1970)
- nonce
- index
- ...

Nice, we will target that "data" field, to redirect all the transaction to my account ! Mwahahahaaaa !!! <br>
Here comes the **first layer of unbrekableness security**
The **data** field you're targeting as an evil **mallory** (crypto name for malicious actor) is actually **hashed** (with a hash function, more on that in a bit) along with its index, timestamp, previous block's Hash, and nonce. What's the problem ? I change the data , I chop & mix all of this with the hash function and we're good...Actually nope => Remember that each block stores a **reference to the previous block** (which is the hash of previous block), so if you change the hash , the "chain" is broken and everybody knows something is wrong here ! <br>
Okay Okay , I will then re-hash all the blocks from the most recent one until the beginning of the chain ! Well mate, that's a fool's errand too. <br>
You forgot the **second big layer of unbrekableness** => it's **distributed**, when a new block pretends to be added, at least 50% of the blockchain network has to agree, so by altering the Blockchain on your little side - hihihi - it will no longer match with the hundreds/thousands of copy on the network --> **you're screwed** <br>
That's a pretty nice intro but of course, this is a very "high-level" overview of how a Blockchain guarantees **data authenticity** (rather than **security** term, since all the data is kind of "public" and distributed, there's no secret here, but it's indeed on the other hand **pure authentic data waranty**).

=> refers to a package that contains a collection of trusted Certificate Authority certificates<br>
used to establish secures connections with websites, servers, services over SSL/TLS ... -->

### **Notes**

#### The PEM, DER what the heck

**der** standard for encoding data structs used in apps like cryptography <br>
It"s a way to represent certificates, keys, other crypto stuff in **binary format** <br>
stands for **D**istinguished **E**ncoding **R**ules. <br>
OpenSSL functions like 'd2i' => Der to Internal <br>
der files most commonly seen in **Java** context

**pem** format, another encoding scheme for **X.509 Certificates** and **keys** <br>
PEM => (Base64 ASCII) <br>
DER => Binary (see above) <br>

PEM for => **P**rivacy **E**nhanced **M**ail, PEM file is a text file containing one or more items in **Base64 ASCII** Encoding, each with plain-text headers and footers
Extensions for pem files , hence `.pem, .crt, .cer .key`

<!-- sudo apt-get install ca-certificates
