import copy

def gaussianSolve(aMatrix,bVector):
    '''
    Gaussian elimination function
    '''

    upper_matrix = copy.deepcopy(aMatrix)
    upper_vect = copy.deepcopy(bVector)

    for idx in range(len(upper_matrix)):
        curr_row = [val/upper_matrix[idx][idx] for val in upper_matrix[idx]]
        upper_vect[idx] /= upper_matrix[idx][idx]
        upper_matrix[idx] = curr_row
        for jdx in range(idx+1,len(upper_matrix)):
            new_row = [jVal-iVal*upper_matrix[jdx][idx] for jVal,iVal in zip(upper_matrix[jdx],curr_row)]
            upper_vect[jdx] -= upper_vect[idx]*upper_matrix[jdx][idx]
            upper_matrix[jdx] = new_row

    solVector = [val for val in upper_vect]
    for idx in range(len(upper_matrix)-1,-1,-1):
        for jdx in range(len(upper_matrix)-1,idx,-1):
            solVector[idx] -= upper_matrix[idx][jdx]*solVector[jdx]

    print upper_matrix
    print upper_vect

    return solVector

def testGaussianSolver():
    '''
    This is a known system of linear system of equations for testing the Gaussian solver
    '''

    givenAMatrix = [[1.0, 7.0, 4.0],
                    [2.0, 6.0, 3.0],
                    [3.0, 5.0, 3.0]]
    givenBVector = [27.0, 23.0, 22.0]
    knownSolVector = [1.0, 2.0, 3.0]

    foundSolVector = gaussianSolve(givenAMatrix,givenBVector)

    for idx,(known,found) in enumerate(zip(knownSolVector, foundSolVector)):
        if known != found:
            raise ValueError("Found solution doesn't match found in row {}. {} != {}".format(idx,known,found))

    print "Test passed!!"


if __name__ == '__main__':
    testGaussianSolver()
