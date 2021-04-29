import os
import subprocess
import statistics


worker_nums = [i for i in range(1, 17)]
methods = {
    0: "serial",
    1: "associative",
    #2: "commutative",
    3: "commutative_builtin",
}
grainsizes = [1, 16, 256]

reps = 20

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


def run_with_params(method, grainsize, worker_num):
    print("worker n {}".format(worker_num), end="\t")

    process = subprocess.Popen(
            "make clean".split(' '),
            stdout=subprocess.DEVNULL,
            stderr=subprocess.STDOUT)
    process.wait()

    process = subprocess.Popen(
            "make METHOD={} GRAINSIZE={}".format(method, grainsize).split(' '),
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

    print(result)


for method in methods:
    print(methods[method])
    if method == 0:
        run_with_params(method, 1, 1)
    else:
        for grainsize in grainsizes:
            print("grainsize", grainsize)
            for worker_num in worker_nums:
                run_with_params(method, grainsize, worker_num)
