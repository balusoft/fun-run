def strings(A, n):
   if n <= 0:
      return ['']
   
   return [r + c for r in A for c in strings(A, n-1)]

def strings_2(A, n):
    index_of = {x: i for i, x in enumerate(A)}
    s = [A[0]] * n
    while True:
        yield ''.join(s)
        for i in range(1, n + 1):
            print ("i: ", i)
            print ("s: ", s)
            if s[-i] == A[-1]:  # Last letter of alphabet, can not increment
                s[-i] = A[0]
            else:
                s[-i] = A[index_of[s[-i]] + 1]  # Modify to next letter
                print("break1")
                break
        else:
            print('break2 ')
            break


def strings_3(A, n):
    s = [0] * n
    while True:
        out = [A[s[j]] for j in range(0,n)]
        yield ''.join(out)
        for i in range(1, n + 1):
            print ("i: ", i)
            print ("s: ", s)
            if s[-i] == len(A) - 1:  # Last letter of alphabet, can not increment
                s[-i] = 0
            else:
                s[-i] = s[-i] + 1  # Modify to next letter
                print("break1")
                break
        else:
            print('break2 ')
            break

def strings_4(A, n):
   out = []
   c = [0]*n

   while True:
      out.append("".join([A[k] for k in c]))

      # we added current result, now advance
      i = 0
      end = True
      for i in range(1, n+1):
         end = True
         if c[-i] == len(A) - 1:
            c[-i] = 0
            continue

         c[-i] += 1
         print("break1 i:", i)
         end = False
         break # from for
      
      if end:
         print("i:", i)
         break # from while
   return out
for s in strings_4(['0', '1', '2'], 2):
   print ("loopout:", s)


#print("strings:", [s for s in strings_2(['0', '1', '2'], 2)])
# complexity is K^n ; here k = len(A)