import os
import subprocess
import statistics


arr_lens = [10]
vector_lens = [2, 8, 16, 32, 64, 128]
worker_nums = [1, 2, 4, 8]

reps = 3

INF = 10000


class Result(object):
    def __init__(self):
        self.times = []
        self.value = None
        self.extras = []

    def insert(self, input_str):
        time = input_str.split("\t")[0]
        value = input_str.split("\t")[1]
        extra = " ".join(input_str.split("\t")[2:])

        if self.value is None:
            self.value = value
        else:
            if self.value != value:
                raise AssertionError("Wrong answer!")
        self.times.append(float(time))
        self.extras.append(extra)

    @property
    def min(self):
        return min(self.times)

    @property
    def stdev(self):
        return statistics.stdev(self.times)

    def __str__(self):
        return "{:.6f}\t{:.5f}  \t{}".format(self.min, self.stdev, self.extras)


for arr_len in arr_lens:
    for worker_num in worker_nums:
        for vector_len in vector_lens:
            process = subprocess.Popen(
                    "make clean".split(' '),
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.STDOUT)
            process.wait()

            process = subprocess.Popen(
                    "make ARR_LEN={} VECTOR_LEN={}".format(
                        arr_len, vector_len).split(' '),
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.STDOUT)
            process.wait()

            print("Arr len {}, vector len {}, worker number {}".format(
                arr_len, vector_len, worker_num))

            serial = Result()
            asso = Result()
            com = Result()

            for i in range(reps):
                command = "CILK_NWORKERS={} taskset -c 1-{} ./main".format(
                    worker_num, worker_num)
                output = os.popen(command).read()

                output = output.strip().split("\n")

                serial.insert(output[0])
                asso.insert(output[1])
                com.insert(output[2])

            print(serial)
            print(asso)
            print(com)
