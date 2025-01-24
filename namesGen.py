import random
import names
import time

def generate_id():
    return f"{random.randint(0, 999):03d}-{random.randint(0, 9999999):07d}"
def generate_name():
    first_name = names.get_first_name()
    last_name = names.get_last_name()
    middle_name = names.get_first_name()  # Using the same function to generate a middle name
    return f"{first_name} {last_name} {middle_name}"
def generate_line():
    return f"{generate_id()} {generate_name()}"
def generate_lines(num_lines, duplicate_probability=0.1):
    i=0
    while i<num_lines:
        line = generate_line()
        if random.random() < duplicate_probability:
            yield line
            i+=1
        if(i<num_lines):
            yield line
            i+=1

# Main entry point of the script
if __name__ == "__main__":
    num_lines = 1_000_000
    duplicate_probability =1000/1000000
    iterTimes=[1]
    dupCount=0
    with open("keys-unsorted.txt","w") as F: 
        with open("keys-duplicates.txt","w") as Fdup: 
            Fdup.write("List of intended duplicates:\n")
            lastLine=""
            t=time.time()
            for i,line in enumerate(generate_lines(num_lines, duplicate_probability)):
                iterTimes=iterTimes[:99]+[time.time()-t]
                t=time.time()
                if(line==lastLine):
                    Fdup.write(line+"\n")
                    dupCount+=1
                F.write(line+"\n")
                lastLine=line
                if i%100==0:
                    #display info
                    avgIterTime=sum(iterTimes)/len(iterTimes)
                    itemPerSec=1/avgIterTime
                    timeLeft=(num_lines-i)/itemPerSec
                    print(f"GEN: {i}, l/s:{round(itemPerSec)}, time left:{round(timeLeft/60)}m dup:{dupCount}",end="\r")
