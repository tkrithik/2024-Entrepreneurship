import json

def encrypt_ph(ph_value):
    digit_map = {
        '0': 'A', '1': 'B', '2': 'C', '3': 'D', '4': 'E',
        '5': 'F', '6': 'G', '7': 'H', '8': 'I', '9': 'J'
    }
    
    ph_str = str(ph_value)
    integer_part, decimal_part = ph_str.split('.')
    encrypted_integer = digit_map[integer_part]
    encrypted_decimal = ''
   
    if decimal_part:
        encrypted_decimal = digit_map[decimal_part]
    
    encrypted_ph = encrypted_integer + encrypted_decimal
    return encrypted_ph

with open('ph.json', 'r') as f:
    ph_data = json.load(f)

encrypted_data = {key: encrypt_ph(value) for key, value in ph_data.items()}

with open('data.json', 'w') as f:
    json.dump(encrypted_data, f, indent=4)


