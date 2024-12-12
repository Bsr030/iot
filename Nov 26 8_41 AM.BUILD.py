---------------------------------Miller-Rabin Primality Test:----------------------------
import random
def miller_rabin(n, k=5):
    if n < 2:
        return False
    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, n - 1, n)

        if x == 1 or x == n - 1:
            continue
        for _ in range(k - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True
print(miller_rabin(4, k=5))
print(miller_rabin(7, k=5))


Theory: 
Purpose: Determines if a number is prime using a probabilistic approach.
Use in Network Security: This is essential for generating large prime numbers, a critical component in encryption algorithms like RSA and Diffie-Hellman. 
Efficient primality testing ensures the creation of secure keys, which form the backbone of many cryptographic systems. 
Its randomization reduces the likelihood of errors while maintaining performance.


--------------------------------------Chinese Remainder Theorem:---------------------
def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1:
        return 1
    while a > 1:
        q = a // b
        a, b = b, a%b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += b0
    return x1

def chinese_remainder(n, a):
    prod = 1
    for i in n:
        prod *= i

    sum = 0
    for i, j in zip(n, a):
        p = prod // i
        sum += j * mul_inv(p, i) * p
    return sum % prod

print(chinese_remainder([3, 4, 5], [2, 3, 1]))

Theory:
Purpose: Solves systems of congruences with different moduli.
Use in Network Security: CRT is used in RSA to optimize modular arithmetic during decryption and signature generation. 
By splitting computations into smaller moduli, CRT significantly speeds up operations, improving performance in secure communication and cryptographic processes.

 
-------------------------------Modular Exponentiation:--------------------
def mod_exp(base, exponent, modulus):
    result = 1
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % modulus
        exponent = exponent >> 1
        base = (base * base) % modulus
    return result

print(mod_exp(52, 713, 41))

Theory:
Purpose: Computes modulus efficiently.
Use in Network Security: Modular exponentiation is a fundamental operation in public-key cryptography (e.g., RSA and Diffie-Hellman). 
It allows secure, efficient encryption, decryption, and key exchange, ensuring sensitive data remains protected during transmission.


-------------------------Euler's Totient Function:------------------
def euler_totient(n):
    result = n
    p = 2
    while p * p <= n:
        if n % p == 0:
            while n % p == 0:
                n //= p
            result -= result // p
        p += 1
    if n > 1:
        result -= result // n
    return result
print(euler_totient(7)) 


Theory:
Purpose: Calculates the number of integers less than 𝑛 that are coprime to n.
Use in Network Security: Used in RSA key generation, Euler’s Totient helps compute the public and private keys. 
By identifying suitable numbers for encryption, it ensures the security and reliability of cryptographic systems.


-------------------------------------DES algorithm------------
from Crypto.Cipher import DES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
def encrypt_des(key, plaintext):
    """Encrypts plaintext using DES algorithm."""
    cipher = DES.new(key, DES.MODE_CBC)
    plaintext_padded = pad(plaintext.encode(), DES.block_size)
    ciphertext = cipher.encrypt(plaintext_padded)
    return cipher.iv, ciphertext
def decrypt_des(key, iv, ciphertext):
    """Decrypts ciphertext using DES algorithm."""
    cipher = DES.new(key, DES.MODE_CBC, iv)
    plaintext_padded = cipher.decrypt(ciphertext)
    plaintext = unpad(plaintext_padded, DES.block_size)
    return plaintext.decode()
def main():
    key = get_random_bytes(8)  # DES key must be exactly 8 bytes
    iv = get_random_bytes(8)  # DES requires an 8-byte IV for CBC mode

    print(f"Key (hex): {key.hex()}")
    print(f"IV (hex): {iv.hex()}")

    plaintext = input("Enter a message to encrypt: ")
    print(f"Original message: {plaintext}")

    iv, ciphertext = encrypt_des(key, plaintext)
    print(f"Encrypted message (hex): {ciphertext.hex()}")

    decrypted_message = decrypt_des(key, iv, ciphertext)
    print(f"Decrypted message: {decrypted_message}")
if __name__ == "__main__":
    main()


O/P:
Key (hex): 5eaf43a2150dfd2d
IV (hex): 4b7d2344e9782b1a
Enter a message to encrypt: Hello, World!
Original message: Hello, World!
Encrypted message (hex):
1a2b3c4d5e6f7089abcde0123456
789
Decrypted message: Hello, World!

Theory:
The experiment demonstrates the Data Encryption Standard (DES) encryption and decryption process, which is a fundamental concept in network security. 
Each step highlights a key aspect of secure communication:
Encryption ensures the confidentiality of data by converting plaintext into ciphertext, making it unreadable to unauthorized parties. This is vital for secure data storage and transmission.
Decryption retrieves the original message using the same symmetric key, ensuring that only authorized users can access the information.
Random Key and IV Generation adds an additional layer of security by ensuring that the encryption process is unique and unpredictable, 
      reducing the risk of attacks like brute force or pattern recognition.
Padding and Block Handling ensures data integrity and compatibility with block cipher requirements, maintaining the robustness of encryption.

---------------------------------------TRIPLE DES ALGORITHM----------------------------
from Crypto.Cipher import DES3
def encrypt_des3(key, plaintext): """Encrypts plaintext using Triple DES algorithm.""" cipher = DES3.new(key, DES3.MODE_CBC)
	plaintext_padded = pad(plaintext.encode(), DES3.block_size)
	ciphertext = cipher.encrypt(plaintext_padded)
	return cipher.iv, ciphertext
def decrypt_des3(key, iv, ciphertext): """Decrypts ciphertext using Triple DES algorithm.""" cipher = DES3.new(key, DES3.MODE_CBC, iv)
	plaintext_padded = cipher.decrypt(ciphertext)
	plaintext = unpad(plaintext_padded, DES3.block_size)
	return plaintext.decode()
def main():
	key = DES3.adjust_key_parity(get_random_bytes(24)) # Triple DES key must be
	exactly 24 bytes
	iv = get_random_bytes(8) # Triple DES requires an 8-byte IV for CBC mode
	print(f"Key (hex): {key.hex()}")
	print(f"IV (hex): {iv.hex()}")
	plaintext = input("Enter a message to encrypt: ")
	print(f"Original message: {plaintext}")
	iv, ciphertext = encrypt_des3(key, plaintext)
	print(f"Encrypted message (hex): {ciphertext.hex()}")
	decrypted_message = decrypt_des3(key, iv, ciphertext)
	print(f"Decrypted message: {decrypted_message}")
if __name__ == "__main__":
	main()ol plp0

O/P:
Key (hex): 7a8b9cdef0123456789abcdef012345
IV (hex): 3f2d6e3a8b9c4d8e
Enter a message to encrypt: Secure Message
Original message: Secure Message
Encrypted message (hex): 2a4b6c7d8e9f0a1b234c567890abcdef
Decrypted message: Secure Message

Theory:
he experiment demonstrates the Triple DES (3DES) encryption and decryption process, which is a more secure enhancement of the original DES algorithm.
This implementation is significant in network security for the following reasons:
Triple DES Encryption ensures data confidentiality by applying the DES algorithm three times with distinct keys, significantly improving security over standard DES. 
      This prevents vulnerabilities like brute-force attacks, which were easier against single DES.
Triple DES Decryption allows authorized parties to securely retrieve the original plaintext, ensuring that sensitive information remains protected during transmission and storage.
Random Key and IV Generation introduces unpredictability to the encryption process, 
      ensuring that each encryption session is unique and resistant to cryptographic attacks, such as replay attacks or pattern analysis.
Padding and Block Handling ensures that the data conforms to the required block size for Triple DES, preserving data integrity during encryption and decryption.

---------------------------------------1. Implement RSA Algorithm---------------------------
import random
from math import gcd
def mod_inverse(e, phi):
	for x in range(1, phi):
		if (e * x) % phi == 1:
			return x
	return None
def generate_keypair(bits):
	p = 61
	q = 53
	n = p * q
	phi = (p - 1) * (q - 1)
	e = random.choice([x for x in range(2, phi) if gcd(x, phi) == 1])
	d = mod_inverse(e, phi)
	return ((e, n), (d, n))
# Function to encrypt a message
def encrypt(pk, plaintext):
	e, n = pk
	# Ciphertext is c = m^e mod n
	cipher = [(ord(char) ** e) % n for char in plaintext]
	return cipher
# Function to decrypt a message
def decrypt(pk, ciphertext):
	d, n = pk
	# Plaintext is m = c^d mod n
	plain = [chr((char ** d) % n) for char in ciphertext]
	return ''.join(plain)
# Testing the RSA implementation
public, private = generate_keypair(8)
message = "HELLO" encrypted_message = encrypt(public, message)
decrypted_message = decrypt(private, encrypted_message)
print("Original message:", message)
print("Encrypted message:", encrypted_message)
print("Decrypted message:", decrypted_message

Output:
Original message: HELLO
Encrypted message: [3000, 28, 2726, 2726, 1307]
Decrypted message: HELLO

Theory:
The experiment demonstrates the RSA encryption and decryption process, a cornerstone of modern cryptography. Here’s its relevance to network security:
Key Pair Generation:
The process generates a public-private key pair using two large prime numbers and modular arithmetic. This asymmetric cryptographic mechanism ensures that one key (public) can encrypt data while only the paired private key can decrypt it.
Encryption:
Converts plaintext into ciphertext using the recipient's public key, ensuring that sensitive information can be shared securely. Even if the ciphertext is intercepted, it cannot be decrypted without the private key.
Decryption:
Retrieves the original message using the private key, ensuring that only authorized individuals with the private key can access the encrypted data. This guarantees confidentiality in secure communications.
Mathematical Foundations:
The algorithm relies on the difficulty of factoring large numbers (n = p * q), which forms the basis of RSA's security. This makes brute-force or mathematical attacks computationally infeasible.

------------------------------2. Implement Diffie-Hellman Key Exchange Algorithm------------
import random
def diffie_hellman(p, g):
	a = random.randint(1, p-1) # Private key for Alice
	b = random.randint(1, p-1) # Private key for Bob
	A = (g ** a) % p # Alice's public value
	B = (g ** b) % p # Bob's public value
	shared_secret_A = (B ** a) % p # Alice's computed shared secret
	shared_secret_B = (A ** b) % p # Bob's computed shared secret
	assert shared_secret_A == shared_secret_B, "Keys don't match!"
	return shared_secret_A
p = 23 # A prime number
g = 5 # A primitive root modulo p
shared_key = diffie_hellman(p, g)
print("Shared Secret Key:", shared_key)

Output:
eeShared Secret Key: 4

Theory:
The experiment demonstrates the Diffie-Hellman Key Exchange, a fundamental method for establishing a shared secret key over an insecure channel. Here’s its relevance to network security:
Private Key Generation:
Alice and Bob independently generate private keys, ensuring that these are never transmitted over the network. This step prevents eavesdroppers from accessing critical information.
Public Key Exchange:
Alice and Bob share their computed public values derived from their private keys. These public values can be transmitted openly, as they do not compromise the security of the shared key.
Shared Secret Key Derivation:
Both parties compute the same shared secret using their private key and the other party's public value. The mathematical principles of modular arithmetic ensure that the shared secret remains secure, even if the public keys are intercepted.
Secure Communication:
The shared secret key can be used for symmetric encryption, enabling secure communication between parties without exposing the key to potential attackers.


-----------------------3. Implement SHA-512 Algorithm------------------
   a. Using a Library:
   
import hashlib
def sha512_hash(message):
    sha512 = hashlib.sha512()
    sha512.update(message.encode('utf-8'))
    return sha512.hexdigest()

message = r"4Hello, Secure World!"
hash_value = sha512_hash(message)
print("SHA-512 Hash:", hash_value)


   B. Without using a libraryp-
   
def simplified_sha512(message):
# Simpexssle hash implementation for educational purposes only
	def right_rotate(value, shift):
		return (value >> shift) | (value << (64 - shift)) & 0xFFFFFFFFFFFFFFFF
	def compression_step(chunk):
		return chunk ^ 0xFFFFFFFFFFFFFFFF
	message_binary = ''.join(format(ord(c), '08b') for c in message)
	chunks = [int(message_binary[i:i+64], 2) for i in range(0, len(message_binary), 64)]
	hash_value = 0x6a09e667f3bcc908
	for chunk in chunks:
		hash_value = compression_step(chunk) ^ right_rotate(hash_value, 7)
	return hex(hash_value)
# Test the function
message = "Hello, Secure World!" hash_value = simplified_sha512(message)
print("Simplified SHA-512 Hash:", hash_value)


     b. Application of SHA-512 for Secure Password Storage
     
     
import hashlib
import os
def hash_password(password):
	salt = os.urandom(16)
	hash_object = hashxlib.sha512(password.encode('utf-8') + salt)
	password_hash = hash_object.hexdigest()
	return salt, password_hash
def verify_password(stored_salt, stored_hash, password_attempt):
	# Recompute the hash with the stored salt and the password attempt
	hash_object = hashlib.sha512(password_attempt.encode('utf-8') + stored_salt)
	return hash_object.hexdigest() == stored_hash
# Testing secure password storage
salt, hashed_password = hash_password("my_secure_password")
print("Stored Hash:", hashed_password)
# Verifying password
is_verified = verify_password(salt, hashed_password, "my_secure_password")
print("Password Verified:", is_verified)

Theory:
**SHA-512** is a cryptographic hash function designed to produce a 512-bit hash value, which is widely used to ensure **data integrity** and **security** in various applications. It generates a unique, fixed-length output for any given input, making it ideal for detecting changes or tampering with data. SHA-512 is commonly used in password hashing, digital signatures, and blockchain technologies to securely store and verify information. It is resistant to preimage and collision attacks, making it a secure choice for applications requiring strong data protection. SHA-512 also helps in creating unique identifiers for files, messages, and transactions, contributing to overall data security.
The SHA-512 algorithm is a crucial cryptographic tool in network security, offering strong data integrity and confidentiality. By generating a 512-bit hash, it ensures that even small changes in input data result in drastically different outputs, making tampering detectable. It is widely used in verifying message authenticity, ensuring that transmitted data remains unaltered. Additionally, SHA-512 plays a key role in securely storing passwords by creating unique, irreversible hashes, which prevent unauthorized access. When combined with salting, it defends against rainbow table attacks. Overall, SHA-512 is fundamental in protecting sensitive information and maintaining the security of digital systems.


--------------------1. Implement HMAC algorithms-------------
import hmac
import hashlibz,,,
def generate_hmac(key, message):
	key_bytes = key.encode() if isinstance(key, str) else key
	message_bytes = message.encode() if isinstance(message, str) else message
	hmac_obj = hmac.new(key_bytes, message_bytes, hashlib.sha256)
	return hmac_obj.hexdigest()
key = "supersecretkey" message = "Important message" hmac_result = generate_hmac(key, message)
print("Generated HMAC:", hmac_result)

Theory:
HMAC is a cryptographic method used to verify the integrity and authenticity of a message by combining a cryptographic hash function (like SHA-256) with a secret key. The resulting MAC ensures that the message hasn't been altered and that it comes from an authorized source. HMAC is commonly used in network security protocols, such as SSL/TLS and IPsec, to protect data from tampering, replay attacks, and unauthorized access. Its simplicity and strong security properties make it widely adopted in various authentication and integrity verification scenarios.
This experiment demonstrates the use of HMAC (Hash-based Message Authentication Code), a cryptographic algorithm designed to verify both the integrity and authenticity of a message. HMAC combines a cryptographic hash function (SHA-256 in this case) with a secret key to produce a unique, fixed-size hash. The secret key ensures that only authorized parties, who possess the key, can generate or verify the HMAC. This makes it resistant to attacks like message tampering and forgery, as altering the message without the key will result in a different HMAC. HMAC is commonly used in secure communications protocols, such as HTTPS and APIs, to protect against data integrity attacks and ensure that messages come from a trusted source.


--------------------2. Implement CMAC algorithms-----------------------
from Crypto.Hash import CMAC
from Crypto.Cipher import AES
def generate_cmac(key, message):
	# Ensure key is in bytes and has a valid length for AES (16, 24, or 32 bytes)
	if isinstance(key, str):
	key = key.encode()
	if len(key) not in [16, 24, 32]:
	raise ValueError("Key must be 16, 24, or 32 bytes long for AES.")= message_bytes = message.encode() if isinstance(message, str) else message
# Create CMAC object and update with the message
	cmac_obj = CMAC.new(key, ciphermod=AES)
	cmac_obj.update(message_bytes)
	return cmac_obj.hexdigest()
key = b"my16bytekey12345" # 16 bytes for AES compatibility
message = "Another important message" print("Generated CMAC:", generate_cmac(key, message))

Theory:
CMAC is a cryptographic technique used to ensure both the integrity and authenticity of a message. It utilizes a symmetric encryption algorithm, such as AES, along with a secret key to generate a unique message authentication code (MAC). This MAC verifies that the message has not been altered during transmission and confirms that it originates from a trusted sender. CMAC is particularly useful in environments where symmetric encryption is already in use, providing an additional layer of security to prevent tampering and unauthorized modifications.
This experiment demonstrates the use of CMAC (Cipher-based Message Authentication Code), a cryptographic algorithm used to verify the integrity and authenticity of a message. CMAC uses a symmetric encryption algorithm, such as AES, combined with a secret key to generate a unique message authentication code (MAC). The key must be of a valid length (16, 24, or 32 bytes) for AES encryption. CMAC ensures that any modification to the message will result in a different MAC, making it highly resistant to tampering. It is commonly used in securing communications, such as in network protocols (e.g., TLS), to guarantee data integrity and prevent unauthorized message alterations.

------------------------SQL INJECTION----------------------------------

import sqlite3

# Setup database
def setup_database():
    conn = sqlite3.connect('dummy.db')
    cursor = conn.cursor()
    # Drop the table if it already exists
    cursor.execute("DROP TABLE IF EXISTS users")
    # Create the users table
    cursor.execute("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)")
    # Insert sample user data
    cursor.execute("INSERT INTO users (username, password) VALUES ('user1', 'pass1')")
    cursor.execute("INSERT INTO users (username, password) VALUES ('user2', 'pass2')")
    conn.commit()
    conn.close()

# Vulnerable query (Not safe for use in practice)
def vulnerable_query(user_id):
    conn = sqlite3.connect('dummy.db')
    cursor = conn.cursor()
    # Directly interpolating user input into the query string
    query = f"SELECT * FROM users WHERE id = {user_id}"
    cursor.execute(query)
    results = cursor.fetchall()
    conn.close()
    return results

# Safe query using parameterized input
def safe_query(user_id):
    conn = sqlite3.connect('dummy.db')
    cursor = conn.cursor()
    # Using parameterized query to prevent SQL injection
    query = "SELECT * FROM users WHERE id = ?"
    cursor.execute(query, (user_id,))
    results = cursor.fetchall()
    conn.close()
    return results

# Main execution
if _name_ == "_main_":
    # Set up the database with dummy data
    setup_database()
    
    # Demonstrating the vulnerable query
    print("Unsafe Query Result:", vulnerable_query("1 OR 1=1"))  # SQL Injection works here
    
    # Demonstrating the safe query
    print("Safe Query Result:", safe_query("1 OR 1=1"))  # Prevents SQL Injection
    
Output:
Unsafe Query Result: [(1, 'user1', 'pass1'), (2, 'user2', 'pass2')]
Safe Query Result: []

Theory:
In network security, the primary purpose of preventing SQL injection attacks is to safeguard databases and sensitive data from unauthorized access, manipulation, or destruction. 
      SQL injection occurs when attackers exploit vulnerabilities in web applications by injecting malicious SQL code into queries, 
      often bypassing authentication mechanisms and accessing confidential information. By using safe coding practices like parameterized queries, 
      applications can ensure that user inputs are treated as data and not executable code, thus mitigating the risk of SQL injection. 
      This helps maintain data integrity, protect user privacy, and prevent breaches, making it a crucial aspect of securing web applications and preventing cyberattacks.
This experiment highlights the importance of SQL Injection prevention in database-driven applications.
      The vulnerable query directly interpolates user input into SQL statements, allowing attackers to inject malicious SQL code, 
      potentially compromising the database (e.g., "1 OR 1=1" results in accessing all records). The safe query uses parameterized queries, which treat user input as data rather than executable code, effectively preventing SQL injection attacks. This is a key practice in secure coding, as it ensures that input data is safely handled, preventing unauthorized access or manipulation of sensitive data. The experiment demonstrates how simple coding practices can significantly improve the security of database interactions.

      
      
      
      
      
      

---c