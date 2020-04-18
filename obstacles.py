import numpy as np
coordinates = np.random.randint(1,100,size=(10,4))
with open("obs.txt","w") as f:
    f.write("\n".join(" ".join(map(str, x)) for x in coordinates)
)
