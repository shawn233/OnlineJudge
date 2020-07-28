# File Structure

This folder is constituted of my solutions and thoughts for problems on Leetcode and a script to execute solutions locally, executing solutions given an index number of the problem. Each folder identifies a problem with its name. Naming format of folders are `<index>-<problem_name>`. Inside each problem folder is a solution script named `solution.cpp`.

To verify a solution, modify `solve.py exec/solve.cpp` and run

```bash
python solve.py
```

# Algorithm Sample Problems

Boyer-Moore majority voting algorithm: 169, 229

Backtracing: 217, 219

# 引子

2020.01.15 北海，广西，CN

今天开始做Leetcode，像是要登一座仰望了很久的山，山脚下先写几句话鼓励自己。因为知道山路必然坎坷，希望我某一天迷失的时候，这些话能帮自己找回方向。

久仰Leetcode的大名，一直当作找工作的法宝。网上传闻刷题上千的大神怎样风光，窃不以为然。如果能仅凭刷题，领悟编程的法门，何不将CS的大学四年课程，开设成刷题训练班，到了找工作时，谁刷题多，谁就厉害。我也曾经写过Leetcode上近100道的Easy题目，似乎的确锻炼了我写代码的能力，代码写多后渐渐摸到了一些门路。但我以为，代码熟练工远不配程序员之称，比之培训班出身的码农，科班出身的优势在于从刷题里学不到的知识，比如Hardware，比如OS，比如Security，甚至还有Programming Language。在合格的程序员眼中，代码不仅是命令CPU干活的工具，而是一个以理论为依据，科学协调CPU，内存，硬盘，乃至显卡等工作的指挥官。

既然我认为刷题与应聘时的优势无关，那么我是否就是一个十足的反对做题者呢？在这一件事情上，我采取的态度，和我通常看待其他事情的态度一样，是中庸的。我认为科班生们虽然不需要将键盘敲出韶华易逝的速度，但也不能慢，最好是和培训班打个平手，然后再在理论上一决雌雄。简单来说，培训班能做到的，我们能做到，比如写Leetcode，而培训班不能做到的，我们最好也能做到，比如谈理论。因此，科班生辛苦一些，既要抓课本，做题也不能疏忽。

想到我两年之后面对就业市场，如果想要有拿得出手的资本，第一关便是要具备不低于培训班学生的算法素质。至少，Leetcode上常见的算法出不得错。

借鉴知乎上呼声甚高的刷题方法，我首先要将几个基础的data structure tags做完，然后再按照List做题。

现在的我便是抱着和培训班在算法素质上打个平手的心态，开始爬山了。


