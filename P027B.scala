object P027B extends App {
  val n = readInt
  var wins   = (for (i <- 0 to n-1) yield 0) toArray
  var losses = (for (i <- 0 to n-1) yield 0) toArray
  var ids    = (for (i <- 0 to n-1) yield i) toList;
  for (i <- 1 to n*(n-1)/2 - 1) {
    val opponents = readLine.split(' ').map(x => x.toInt-1)
    wins(opponents(0))   += 1
    losses(opponents(1)) += 1
  }
  ids = ids.sortWith(wins(_) < wins(_))
  val missed = ids.zipWithIndex.filter(x => wins(x._1) != x._2)
  printf("%d %d\n", missed(0)._1+1, ids.find(x => wins(x) + losses(x) != n-1).get+1)
}
