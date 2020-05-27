import random


output_file_vector_data = open("vector_data.txt", "w")

NUM_ELEMENT = 10000
RANGE = 10000

for i in range(0, NUM_ELEMENT):
    output_file_vector_data.write(str(random.randrange(0, RANGE, 1)) + "\n")

output_file_vector_data.close()
