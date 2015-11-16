library(sna)         
library(network)
library(rgl)
library(networkDynamic)

#preset number of type-nodes
V <- 100
W1 <- 7
W2 <- 7

#random number of type-nodes
#V <- sample(0:10, 1)
#W1 <- sample(0:10, 1)
#W2 <- sample(0:10, 1)

#node vector
n <- c(0, V, W1, W2)

#node colors
colors <- 1:(length(n)-1)
Col <- rep(0, times=sum(n))
names(colors) <- c("red", "cyan", "green")


#node weights
#w <- replicate

#initialize GCA
#g <- rep(0, times=(sum(n))^2)
g <- replicate(sum(n)^2, sample(0:1, 1), simplify="array")
G <- matrix(g, nrow=sum(n), ncol=sum(n))

#create like-components
for (i in 1:(length(n)-1)){
  a <- rep(0, times=n[i+1]^2)
  #a <- replicate(n[i+1]^2, sample(0:1, 1), simplify="array")
  A <- matrix(a, nrow=n[i+1], ncol=n[i+1])
  for(p in 1:n[i+1]){
    for (q in 1:n[i+1]){
      A[p,q] -> A[q,p]
      A[p,p] = 0
    }
  }
  b <- sum(n[1:i])+1
  c <- sum(n[1:(i+1)])
  count <- length(b:c)
  G[b:c, b:c] <- A[1:count, 1:count]
  col<- rep(names(colors)[i], times=count)
  #print(col)
  Col[b:c] <- col[1:count]
  #print(Col)
}

#ensure inhibition of higher access
G[1:V, (V+W1+1):sum(n)] <- 0

#prohibit resource binding
G[(V+1):sum(n), (V+1):sum(n)] <- 0

#limit binding
for(i in  1:V){
  G[i, (V+1):(V+W1)] = sample(0:1, 1)
  while(sum(G[i, (V+1):(V+W1)]) > 1){
    G[i, sample((V+1):(V+W1), 1)] <- 0
  }
}

#prioritize binding
for (i in 1:V){
  for (j in (V+1):(V+W1)){
    if (G[i,j]== 1){
      G[i, (V+W1+1):sum(n)]=sample(0:1, 1)
    }
    while(sum(G[i, (V+W1+1):(sum(n))]) > 1){
      G[i, sample((V+W1+1):sum(n), 1)] <- 0
    } 
  }
}
#print(G)

#allow for binding of agents if specific conditions are met
vec <- numeric()

for(i in 1:V){
  for (j in (V+W1+1):(sum(n))){
    if(G[i, j]==1){
      vec <- c(vec, i)
    }
  } 
}
print(vec)
lvec <- length(vec)
uvec <- unique(vec)
for(i in 1:lvec){
  sveci <- sample(i, 1)
  for (j in 1:lvec){
    svecj <- sample(j, 1)
    G[uvec[sveci], uvec[svecj]] <- 1
  }
}
#print(uvec)
#print(sample(vec, 1))
#G[uvec[svec], 1), uvec[svec],1] <- 1
diag(G)=0

if (length(uvec) == 1){
  G[1:V, 1:V] = 0
}

#print(G[1:V, 1:V])


#make GCA undirected
for (i in 1:sum(n)){
  for (j in 1:sum(n)){
    G[j, i] <- G[i,j]
  }
}

print(G[1:V, 1:V])
#print(G)

#create network
net <- network(G, directed=FALSE)
#net %v% "weights" <- w

#plot network
gplot(net, vertex.col=Col)
#gplot3d(net, vertex.col=Col)

#agent adjacency matrix
agents <- G[1:V, 1:V]
#print(agents)

#create society
soc <- network(agents, directed = FALSE)
#wagents <- w[(sum(n)*(1:V))+(1:V)]
#soc %v% "weights" <- wagents

#plot society
gplot(soc, vertex.col=Col[1:V])

#eliminate dead nodes
zeros <- rep(0, times=V)

for(i in V:1){
  #print(agents)
  test <- agents[i,]==zeros
  #print(test)
  if(all(test)==1){
    agents <- agents[-i, -i]
  }
}

V2 <- sqrt(length(agents))

n2 <- c(0, V2, W1, W2)
#print(G)
#print(V2)
#print(agents)
'for(i in 1:V-1){
  if (sum(G[i, (i+1):V])>0){
    G[i, (V+1):sum(n)] <- G[i, (V+1):sum(n)]
  }
}'

G[1:V2, 1:V2] <- agents[1:V2, 1:V2]
print(uvec)
print(G)
'for(i in 1:V2){
  #if (G[i,(i+1): ]
  print(G[i,])
  G[i, (V2+1):sum(n2)] <- G[uvec[i], (V2+1):sum(n2)]
}'
#print(G)
for(i in 1:sum(n2)){
  for(j in 1:sum(n2)){
    G[j, i] <- G[i,j]
  }
}
#print(G)
#print(G)
#print(G[1:V2, 1:V2])
#print(G[1:V, 1:V])
#print(agents2)
#G[1:V2, 1:V2] <- agents
#print(agents)
#node vector

for (i in V:(V2+1)){
  #print(G[1:i, 1:i])
  G <- G[-i, -i]
}
print(G[1:V2, 1:V2])
#print(G)
#node colors
colors2 <- 1:(length(n2)-1)
Col2 <- rep(0, times=sum(n2))
names(colors2) <- c("red", "cyan", "green")

for (i in 1:(length(n2)-1)){
  a2 <- rep(0, times=n2[i+1]^2)
  #a <- replicate(n[i+1]^2, sample(0:1, 1), simplify="array")
  A2 <- matrix(a2, nrow=n2[i+1], ncol=n2[i+1])
  for(p in 1:n2[i+1]){
    for (q in 1:n2[i+1]){
      A2[p,q] -> A2[q,p]
      A2[p,p] = 0
    }
  }
  b2 <- sum(n2[1:i])+1
  c2 <- sum(n2[1:(i+1)])
  count2 <- length(b2:c2)
  #print(count2)
  #G[b2:c2, b2:c2] <- A2[1:count2, 1:count2]
  col2<- rep(names(colors2)[i], times=count2)
  #print(col2)
  Col2[b2:c2] <- col2[1:count2]
  #print(Col2)
}
#print(Col2)

#print(G[1:V, 1:V])
for (i in V:(V2+1)){
  #print(G[1:i, 1:i])
  G <- G[-i, -i]
}
#print(G[1:V2, 1:V2])
#create society
socdos <- network(agents, directed = FALSE)
#wagents <- w[(sum(n)*(1:V))+(1:V)]
#socdos %v% "weights" <- wagents

#plot society
gplot(socdos, vertex.col=Col[1:V2])
#gplot3d(socdos, vertex.col=Col[1:V])
#print(agents)

net2 <- network(G, directed = FALSE)
#net2 %v% "weights" <- w

gplot(net2, vertex.col=Col2)