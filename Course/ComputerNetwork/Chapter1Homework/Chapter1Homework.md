# Computer Network - Chapter 1 Assignment

> 10185101210 陈俊潼, East China Normal University

**1-1. Five routers are to be connected in a point-to-point subnet . Between each pair of routers, the designers may put a high-speed line, a medium-speed line, a low-speed line, or no line. If it takes 100 ms of computer time to generate and inspect each topology, how long will it take to inspect all of them?**

Let the routers be A, B, C, D, E.
So there's AB, AC, AD, AE, BC, BD, BE, CD, CE, DE, a total of 10 different routes.
For each line, there're 4 options. Thus there're 4^10 topologies, requires 104857.6s to inspect all of them.

**1-2. What are two reasons for using layered protocols? What is one possible disadvantage of using layered protocols?**

Advantage:


1. Using layered protocols means the layers can be designed seperately, which is easier to design.
2. Using layered protocols can ensure that the update or modification of one single layer won't affect the higer level or lower level.

Disadvantage:

Layered protocols might be of low efficiency when it comes to transfering single characters. It will add many headers on it and lower the transfer speed. Thus the performance is not good as single-layer protocols.

**1-3. What is the principal difference between connectionless communication and connection-oriented communication? Give one example of a protocol that uses**
**(i) connectionless communication**
**(ii) connection-oriented communication**

The connection-oriented communication contains 3 stages: Connection Setup, Data Transfer and Connection Termination, while connectionless communication doesn't pocess. Besides, the order of data can be guarenteed in connection-oriented communication while in connectionless communicatioin it doesn't have. 

An example of connection-oriented communication is Digital Voice, an example of connectionless communication is E-mail system.

**1-4. In some networks, the data link layer handles transmission errors by requesting that damaged frames be retransmitted. If the probability of a frame's being damaged is p, what is the mean number of transmissions required to send a frame? Assume that acknowledgements are never lost.**

The probability of a frame NOT being damaged $p = 1-p$, so the mean number (Exception E) of transmissions required is $\frac{1}{1-p}$.

**1-5. A system has an n-layer protocol hierarchy. Applications generate messages of length M bytes. At each of the layers, an h-byte header is added. What fraction of the network bandwidth is filled with headers?**

Total header bytes: $hn$. So the fraction is $\frac{hn}{M+hn}$.

**1-6. What is the main difference between TCP and UDP?**

TCP|UDP
:-:|:-:
Connection-oriented Communication|Connectionless Communication
Sequencing|Not Sequencing
Focusing on accuracy and flow control|Focusing on prompt delivery

**1-7. When a file is transferred between two computers, two acknowledgement strategies are possible. In the first one, the file is chopped up into packets, which are individually acknowledged by the receiver, but the file transfer as a whole is not acknowledged. In the second one, the packets are not acknowledged individually, but the entire file is acknowledged when it arrives. Discuss these two approaches.**

If the network connection is relatively stable, the data can be transferred by the whole file, which is of better performance. However if the connection is not stable, the file should be transferred in individual packets and check it's competence every time to ensure the file is successfully transferred.

**1-8. An image is 1024 X 768 pixels with 3 bytes/pixel. Assume the image is uncompressed. How long does it take to transmit it over a 56-kbps modem channel?**
**Over a 1-Mbps cable modem?**
**Over a 10-Mbps Ethernet?** 
**Over 100-Mbps Ethernet?**
**Over gigabit Ethernet?**

The file size is $1024*768*3=2,359,296$ bytes = 18,874,368 bits.

The time it needs is as follows:

Transferring Method | Time
---|---
56-kbps modem channel|5.49min
1-Mbps cable modem|18s
10-Mbps Ethernet|1.8s
100-Mbps Ethernet|0.18s
Gigabit Ethernet|0.018s

**1-9. Suppose the algorithms used to implement the operations at layer k is changed. How does this impact operations at layers k − 1 and k + 1?**

The interface is not changed, so there shouldn't be any impact at layers k - 1 and k + 1.

**1-10. Suppose there is a change in the service (set of operations) provided by layer k. How does this impact services at layers k-1 and k+1?**

For layer k-1, there's no impact. But the operations in layer k+1 should be modified.