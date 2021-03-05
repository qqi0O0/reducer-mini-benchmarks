import os
import subprocess
import statistics


worker_nums = [1, 2, 4, 8]
methods = {
    0: "serial",
    1: "associative",
    2: "commutative",
    3: "commutative_builtin",
}

reps = 3

INF = 10000


class Result(object):
    def __init__(self):
        self.times = []
        self.value = None

    def insert(self, input_str):
        time = input_str.split("\t")[0]
        value = " ".join(input_str.split("\t")[1:])

        if self.value is None:
            self.value = value
        else:
            if self.value != value:
                raise AssertionError("Wrong answer!")
        self.times.append(float(time))

    @property
    def mean(self):
        return statistics.mean(self.times)

    @property
    def stdev(self):
        return statistics.stdev(self.times)

    def __str__(self):
        return "{:.6f}\t{:.5f}".format(self.mean, self.stdev)


def run_benchmark(worker_num):
    print("worker number {}".format(worker_num))

    for method in methods:
        process = subprocess.Popen(
                "make clean".split(' '),
                stdout=subprocess.DEVNULL,
                stderr=subprocess.STDOUT)
        process.wait()

        process = subprocess.Popen(
                "make METHOD={}".format(method).split(' '),
                stdout=subprocess.DEVNULL,
                stderr=subprocess.STDOUT)
        process.wait()

        result = Result()

        for i in range(reps):
            command = "CILK_NWORKERS={} taskset -c 1-{} ./main".format(
                worker_num, worker_num)
            output = os.popen(command).read()
            output = output.strip()
            output = output.split('\n')[1]
            result.insert(output)

        print("{}\t{}".format(methods[method], result))


for worker_num in worker_nums:
    run_benchmark(worker_num)
