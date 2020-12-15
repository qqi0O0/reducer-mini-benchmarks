import os
import subprocess


arr_lens = [10]
vector_lens = [1, 8, 16, 32, 64, 128]
worker_nums = [1, 2, 4, 8]

reps = 3

INF = 10000


for arr_len in arr_lens:
    for vector_len in vector_lens:
        for worker_num in worker_nums:
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

            s = None
            times = [INF] * 3

            for i in range(reps):
                command = "CILK_NWORKERS={} taskset -c 1-{} ./main".format(
                    worker_num, worker_num)
                output = os.popen(command).read()

                output = output.strip().split("\n")
                serial_t, serial_s = output[0].split('\t')
                asso_t, asso_s = output[1].split('\t')
                com_t, com_s = output[2].split('\t')

                if s is None:
                    s = serial_s
                if serial_s != s or asso_s != s or com_s != s:
                    print("Wrong answer!")
                    print(output)

                times[0] = min(times[0], float(serial_t))
                times[1] = min(times[1], float(asso_t))
                times[2] = min(times[2], float(com_t))

            for time in times:
                print(time)
