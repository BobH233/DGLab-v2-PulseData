import os
import json
import re

def extract_values_from_file(file_path):
    pattern = re.compile(r'新值:\s*([0-9A-Fa-f]{2})\s*([0-9A-Fa-f]{2})\s*([0-9A-Fa-f]{2})')
    extracted_values = []
    
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            match = pattern.search(line)
            if match:
                extracted_values.append(''.join(match.groups()))
    
    return extracted_values

def process_directory(directory):
    result = {}
    
    for file_name in os.listdir(directory):
        if file_name.endswith('.txt'):
            file_path = os.path.join(directory, file_name)
            file_key = os.path.splitext(file_name)[0]  # Remove .txt extension
            result[file_key] = extract_values_from_file(file_path)
    
    return result

def main():
    directory = "./OriginalData"
    output_file = "pulse_data.json"
    
    extracted_data = process_directory(directory)
    
    with open(output_file, 'w', encoding='utf-8') as json_file:
        json.dump(extracted_data, json_file, ensure_ascii=False, indent=4)
    
    print(f"JSON数据已保存至 {output_file}")

if __name__ == "__main__":
    main()
