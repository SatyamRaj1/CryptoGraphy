import random
import math
import sys

class RSA:
    def __init__(self):
        self.bitsize = int(input("Enter No. of Bits : "))
        self.Q = self.generatePrime(self.bitsize)
        print("Q")
        print(self.Q)
        self.P = self.Q
        while(self.P==self.Q):
            self.P = self.generatePrime(self.bitsize)
        print("P")
        print(self.P)
        self.N = self.P*self.Q
        self.Phi = (self.P-1)*(self.Q-1)
        self.E = self.generateE(self.Phi)
        print("E")
        print(self.E)
        self.PublicKey = (self.N, self.E)
        self.x_GCD = 0
        self.y_GCD = 0
        self.privateKey = self.calculatePrivateKey(self.E, self.Phi)
        print("D")
        print(self.privateKey)
    def calculatePrivateKey(self, a, Phi):
        sys.setrecursionlimit(2000)
        g = self.gcdExtended(a, Phi)
        if g!=1:
            print("E and Phi GCD is not 1")
            exit()
        return (self.x_GCD%Phi+Phi)%Phi
    
    def miillerTest(self, d, n):
        a = 2 + random.randint(1, n - 4)
        x = self.calculatePower(a, d, n)
        if (x == 1 or x == n - 1):
            return True
    
        while (d != n - 1):
            x = (x * x) % n
            d *= 2
    
            if (x == 1):
                return False
            if (x == n - 1):
                return True
        return False
    
    def isPrime(self, n):
        noOfIteration = 40
        if (n <= 1 or n == 4):
            return False
        if (n <= 3):
            return True
        d = n - 1
        while (d % 2 == 0):
            d //= 2
        for i in range(noOfIteration):
            if (self.miillerTest(d, n) == False):
                return False
        return True
    def generatePrime(self, bitsize):
        rand_int = random.randint(2**(bitsize-1), 2**(bitsize))
        if(rand_int%2==0):
            rand_int+=1
        while(not(self.isPrime(rand_int))):
            rand_int = rand_int+2
        return rand_int

    def generateE(self, n):
        e = random.randint(0, n)
        while(math.gcd(e, n)!=1):
            e = random.randint(0,n)
        return e 
    def gcdExtended(self, a, b):
    
        if (a == 0):
            self.x_GCD = 0
            self.y_GCD = 1
            return b
    
        gcd = self.gcdExtended(b % a, a)
        x1 = self.x_GCD
        y1 = self.y_GCD

        self.x_GCD = y1 - (b // a) * x1
        self.y_GCD = x1
        return gcd
    def Encrypt(self, Message):
        MessageArray = []
        M = 0
        for i in Message:
            if(M*256>=self.N):
                MessageArray.append(M)
                M = 0
            M*=256
            M+=ord(i)
        if(M!=0):
            MessageArray.append(M)
        print("MessageArray Computed")
        # print(MessageArray)
        C = [self.EncryptBlock(i) for i in MessageArray]
        print("CipherArray Computed")
        # print(C)
        cipherText = ""
        for i in C:
            k = i
            while(k!=0):
                cipherText = chr(k%256) + cipherText
                k = k//256
        # print(cipherText)
        return cipherText
    def calculatePower(self, a, n, mod):
        res = 1
        a = a%mod
        while(n>0):
            if(n & 1):
                res = (res*a)%mod
            n = n>>1
            a = (a*a)%mod
        return res 
    def EncryptBlock(self, MessageBlock):
        a = MessageBlock
        return self.calculatePower(a, self.E, self.N)
    def DecryptBlock(self, CipherBlock):
        a = CipherBlock
        return self.calculatePower(a, self.privateKey, self.N)
    def Decrypt(self, CipherText):
        CipherArray = []
        C = 0
        for i in CipherText:
            if(C*256>=self.N):
                CipherArray.append(C)
                C = 0
            C*=256
            C+=ord(i)
        if(C!=0):
            CipherArray.append(C)
        print("CipherArray Computed")
        # print(CipherArray)
        M = [self.DecryptBlock(i) for i in CipherArray]
        print("MessageArray Computed")
        # print(M)
        messageText = ""
        for i in M:
            k = i
            while(k!=0):
                messageText = chr(k%256)+ messageText
                k = k//256
        # print(messageText)
        return messageText

if __name__ == "__main__":
    R = RSA()
    f = int(input("Encrypt Number (1) or File (else) : "))
    if(f==1):
        m = int(input("enter no : "))
        c = R.EncryptBlock(m)
        print("Encrypted : ", c)
        m2 = R.DecryptBlock(c)
        print("Decrypted : ", m2)
    else:
        file_name = input("Enter File Name : ")
        inputfile = open(file_name, 'r', encoding='utf-8')
        outputfile = open("EncryptedFile.txt", 'w', encoding='utf-8')
        Message = ""
        for line in inputfile:
            Message = Message + line 
        # print(Message)
        print("Starting Encryption")
        outputfile.write(R.Encrypt(Message))
        inputfile.close()
        outputfile.close()
        print("Encryption SuccessFull!!!!!!!!")
        inputfile = open("EncryptedFile.txt", 'r', encoding='utf-8')
        outputfile = open("DecryptedFile", 'w', encoding='utf-8')
        Cipher = ""
        for line in inputfile:
            Cipher = Cipher+line 
        # print(Cipher)
        print("Starting Dexrypting")
        outputfile.write(R.Decrypt(Cipher))
        inputfile.close()
        outputfile.close()
    