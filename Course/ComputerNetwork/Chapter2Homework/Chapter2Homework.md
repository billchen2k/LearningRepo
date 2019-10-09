# Computer Networks - Chapter 2 Assignment

> 10185101210 陈俊潼, East China Normal University

 ##### 2-1. A noiseless 8-kHz channel is sampled every 1 msec. What is the maximum data rate?

From Nyquist's theorem we know that maximum data rate = $2Blog_2V$ bits/sec. 

So the maximum data rate = 16kbps.

##### 2-2. If a binary signal is sent over a 3-kHz channel whose signal-to-noise ratio is 20 dB, what is the maximum achievable data rate?

The signal-to-noise ratio is 20dB = $10log_{10}S/N$, so S/N = 100.

From Shannon's theorem we know that te maximum data rate = $Blog_2(1+S/N)$ bits/sec ≈ 19.95 kbits/sec.

##### 2-3. How much bandwidth is there in 0.1 microns of spectrum at a wavelength of 1 micron?

$$\because f=\frac{c}{\lambda} \Rightarrow \frac{df}{d\lambda}=\frac{c}{\lambda^2} \Rightarrow \Delta f=\frac{c}{\lambda^2}\Delta \lambda \\ \therefore \Delta \lambda = 0.1 \times 10^{-6} = 10^{-7} m \\ \therefore \Delta f = 30 \times 10^{12} Hz = 30THz. $$

##### 2-4. It is desired to send a sequence of computer screen images over an optical fiber. The screen is 1920x1200 pixels, each pixel being 24 bits. There are 50 screen images per second. How much bandwidth is needed?

Beacuse the resolution of the screen is 1920x1200, each pixel being 24 bits, so there are: $1920 \times 1200 \times 24 \times 50= 2,764,800,000$ bits to be transferred per sec. 

So the bandwidth of  2.7648 Gbps is needed.

##### 2-5. Radio antennas often work best when the diameter of the antenna is equal to the wavelength of the radio wave. Reasonable antennas range from 1 cm to 5 meters in diameter. What frequency range does this cover?

Becuase $f=c/\lambda$, and the $\lambda$ here is form 1cm to 5 meters,
So f ranges from $3\times10^{10}$ to $6\times10^{7}$ bits/sec, that is 30GHz to 60MHz.

##### 2-6. Ten signals, each requiring 4000 Hz, are multiplexed onto a single channel using FDM. What is the minimum bandwidth required for the multiplexed channel? Assume that the guard bands are 400 Hz wide.

$10 \times 4000 + 9 \times 400 = 43600Hz = 4.36KHz$
So the bandwidth needed is 4.36KHz.

##### 2-7. Why has the PCM sampling time been set at 125 μsec?

The bandwidth of a telephone line is 4KHz, from Nyquist's theorem, the maximum data rate = $2Blog_2V$ bits/sec. So the maximum data rate of this line is 8KHz, that is sampling 8000 times per sec, 125 μsec a time. The data rate won't be more than 8KHz, so sampling more frequently is not necessary.

##### 2-8. Compare the maximum data rate of a noiseless 4-kHz channel using
(a) Analog encoding (e.g., QPSK) with 2 bits per sample.
(b) The T1 PCM system.

(a). The maximum data rate = $2Blog_2V = 2 * 4K * 2$ = 16Kbps
(b). The maximun data rate = $2Blog_2V = 2 * 4K * 7$ = 56Kbps.

##### 2-9. A CDMA receiver gets the following chips: (-1 +1 -3 +1 -1 -3 +1 +1). Assuming the chip sequences defined in Fig. 2-28(a), which stations transmitted, and which bits did each one send?

We know that:

> S=(-1 +1 -3 +1 -1 -3 +1 +1) 
> A=(-1 -1 -1 +1 +1 –1 +1 +1) 
> B=(-1 –1 +1 –1 +1 +1 +1 -1) 
> C=(-1 +1 -1 +1 +1 +1 -1 -1) 
> D=(-1 +1 –1 –1 –1 –1 +1 -1) 

A·S=(+1-1+3+1-1+3+1+1)/8=1 

B·S=(+1-1-3-1-1-3+1-1)/8=-1 

C·S=(+1+1+3+1-1-3-1-1)/8=0 

D·S=(+1+1+3-1+1+3+1-1)/8=1

So for station A, B, C, D, they send bits 1, 1, 0, 1 seperately.

##### 2-10. A cable company decides to provide Internet access over cable in a neighborhood consisting of 5000 houses. The company uses a coaxial cable and spectrum allocation allowing 100 Mbps downstream bandwidth per cable. To attract customers, the company decides to guarantee at least 2 Mbps downstream bandwidth to each house at any time. Describe what the cable company needs to do to provide this guarantee.

A 2-Mbit/s downstream bandwidth guarantee to each house implies at most 50 houses per coaxial cable. Thus, the cable company will need to split up the existing cable into 100 coaxial cables and connect each of them directly to a fiber node.

