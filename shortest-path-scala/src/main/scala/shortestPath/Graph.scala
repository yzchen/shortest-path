package shortestPath

import scala.collection.mutable

class shortestPath {
    type Graph = Map[String, Node]

    def printGraph(graph: Graph) = {
        for (node <- graph) {
            println(node._1 + " : " + node._2.toString)
        }
    }

    def dijkstra(graph: Graph, source: String): Unit = {

        val q = new mutable.PriorityQueue[String]
        q.enqueue(source)

        graph(source).distance = 0
        graph(source).mask = true

        while (q.nonEmpty) {

            val uName = q.dequeue()

            println(uName + " : " + graph(uName).distance)

            for (neighbor <- graph(uName).neighbors) {
                if (graph(neighbor._1).distance > graph(uName).distance + neighbor._2) {
                    graph(neighbor._1).distance = graph(uName).distance + neighbor._2
                    println("  -->" + neighbor._1 + " : " + graph(neighbor._1).distance)

                    if (!graph(neighbor._1).mask) {
                        q.enqueue(neighbor._1)
                        graph(neighbor._1).mask = true
                    }
                }
            }

        }
    }

    def spfa(graph: Graph, source: String): Unit = {

        val q = new mutable.Queue[String]
        q.enqueue(source)

        graph(source).distance = 0
        graph(source).mask = true

        while (q.nonEmpty) {

            val uName = q.dequeue()
            graph(uName).mask = false

            println(uName + " : " + graph(uName).distance)

            for (neighbor <- graph(uName).neighbors) {
                if (graph(neighbor._1).distance > graph(uName).distance + neighbor._2) {
                    graph(neighbor._1).distance = graph(uName).distance + neighbor._2
                    println("  -->" + neighbor._1 + " : " + graph(neighbor._1).distance)

                    if (!graph(neighbor._1).mask) {
                        q.enqueue(neighbor._1)
                        graph(neighbor._1).mask = true
                    }
                }
            }

        }

    }
}

object GraphRun extends shortestPath{
    def main(args: Array[String]): Unit = {
        val A = new Node("A")
        val B = new Node("B")
        val C = new Node("C")
        val D = new Node("D")
        val E = new Node("E")

        val g: Graph = Map("A" -> A, "B" -> B, "C" -> C, "D" -> D, "E" -> E)

        g("A").neighbors = ("B", 7) :: ("C", 1) :: Nil
        g("B").neighbors = ("A", 7) :: ("D", 2) :: Nil
        g("C").neighbors = ("A", 1) :: ("D", 3) :: Nil
        g("D").neighbors = ("B", 2) :: ("C", 3) :: ("E", 2) :: Nil
        g("E").neighbors = ("D", 2) :: Nil

//        dijkstra(g, "A")
        spfa(g, "A")
        printGraph(g)
    }
}
