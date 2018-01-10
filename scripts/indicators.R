library("mco")

# read best-known Pareto front for the instance under consideration
bestknown <- as.matrix(read.table("/home/kayoku/project/OCMulti/instances/best.randomAB100.tsp", dec="."))
# force double
bestknown <- bestknown + 0.0

# read Pareto front approximation found by my favorite algorithm
#monalgo <- read.table("../data-tsp/scalar.randomAB100.tsp")
# instead, I just sample the best-known
monalgo <- as.matrix(read.table("/home/kayoku/project/OCMulti/AB/scalar-1.dat", dec="."))
monalgo <- monalgo + 0.0

#bestknown[sample(nrow(bestknown), 100), ]

# plot theminst
plot(bestknown)
points(monalgo, col='red')

# reference point
refpoint <- c(max(bestknown[,1], monalgo[,1]), max(bestknown[,2], monalgo[,2]))
refpoint <- 1.1 * refpoint

# (inverted) generational distance (to be minimized)
generationalDistance(bestknown, monalgo)

# epsilon indicator (to be minimized)
epsilonIndicator(monalgo, bestknown)

# hypervolume (to be maximized)
dominatedHypervolume(bestknown, refpoint)
dominatedHypervolume(monalgo, refpoint)

# relative hypervolume difference (to be minimized)
(dominatedHypervolume(bestknown, refpoint) - dominatedHypervolume(monalgo, refpoint)) / dominatedHypervolume(bestknown, refpoint)

