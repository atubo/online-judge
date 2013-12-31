object P337A extends App {
  val param = readLine.split(' ').map(_.toInt)
  val n = param(0)
  val a = readLine.split(' ').map(_.toInt).sorted.toList
  println(a.sliding(n).map(l=>l(n-1)-l(0)).min)
}
