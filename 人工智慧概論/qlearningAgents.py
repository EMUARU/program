# qlearningAgents.py
# ------------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from game import *
from learningAgents import ReinforcementAgent
from featureExtractors import *
from backend import ReplayMemory

import nn
import model
import backend
import gridworld


import random,util,math
import numpy as np
import copy

class QLearningAgent(ReinforcementAgent):
    """
      Q-Learning Agent
      Functions you should fill in:
        - computeValueFromQValues
        - computeActionFromQValues
        - getQValue
        - getAction
        - update
      Instance variables you have access to
        - self.epsilon (exploration prob)
        - self.alpha (learning rate)
        - self.discount (discount rate)
      Functions you should use
        - self.getLegalActions(state)
          which returns legal actions for a state
    """
    def __init__(self, **args):
        "You can initialize Q-values here..."
        ReinforcementAgent.__init__(self, **args)

        "*** YOUR CODE HERE ***"
        # 用二維字典將每個狀態的Q值存起來
        self.Q = dict(dict())

    def getQValue(self, state, action):
        """
          Returns Q(state,action)
          Should return 0.0 if we have never seen a state
          or the Q node value otherwise
        """
        "*** YOUR CODE HERE ***"
        # 對存在的情況回傳對應的Q值
        if state in self.Q:
            if action in self.Q[state]:
                return self.Q[state][action]
        # 對不存在的情況回傳0
        return float(0)

    def computeValueFromQValues(self, state):
        """
          Returns max_action Q(state,action)
          where the max is over legal actions.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return a value of 0.0.
        """
        "*** YOUR CODE HERE ***"
        # 獲得目前狀態的合法行為
        legalActions = self.getLegalActions(state)
        # 目前狀態沒有合法行為就回傳0
        if not legalActions:
            return float(0)
        # 取得目前狀態的最大Q值並回傳
        QValues = []
        for action in legalActions:
            QValues.append(self.getQValue(state, action))
        maxQValue = max(QValues)

        return maxQValue

    def computeActionFromQValues(self, state):
        """
          Compute the best action to take in a state.  Note that if there
          are no legal actions, which is the case at the terminal state,
          you should return None.
        """
        "*** YOUR CODE HERE ***"
        # 獲得目前狀態的合法行為
        legalActions = self.getLegalActions(state)
        # 目前狀態沒有合法行為就回傳0
        if not legalActions:
            return None
        # 取得目前狀態的最大Q值
        value = self.computeValueFromQValues(state)
        # 取得符合目前狀態的最大Q值的所有行為
        actions = []
        for action in legalActions:
            QValue = self.getQValue(state, action)
            if QValue == value:
                actions.append(action)
        # 隨機回傳符合目前狀態的最大Q值的一個行為
        randomChoice = random.choice(actions)
        return randomChoice


    def getAction(self, state):
        """
          Compute the action to take in the current state.  With
          probability self.epsilon, we should take a random action and
          take the best policy action otherwise.  Note that if there are
          no legal actions, which is the case at the terminal state, you
          should choose None as the action.
          HINT: You might want to use util.flipCoin(prob)
          HINT: To pick randomly from a list, use random.choice(list)
        """
        # Pick Action
        legalActions = self.getLegalActions(state)
        action = None
        "*** YOUR CODE HERE ***"
        # 靠機率隨機回傳隨機的行為或目前狀態時的準則
        if random.random() < self.epsilon:
            action = random.choice(legalActions)
        else:
            action = self.getPolicy(state)

        return action

    def update(self, state, action, nextState, reward):
        """
          The parent class calls this to observe a
          state = action => nextState and reward transition.
          You should do your Q-Value update here
          NOTE: You should never call this function,
          it will be called on your behalf
        """
        "*** YOUR CODE HERE ***"
        # 因為不知道T和R 所以不能直接用Q狀態更新Q值
        # 令Q(s, a)估計值 大約等於 r + gamma * max(Q(s', a'))
        estimate = reward + self.discount * self.computeValueFromQValues(nextState)
        # 如果Q(s, a)不存在就初始化成0
        if state not in self.Q:
            self.Q[state] = dict()
        if action not in self.Q[state]:
            self.Q[state][action] = float(0)
        # 下面的陳述等價於式子
        # Q(s, a) <- (1 - alpha)Q(s, a) + (alpha)[r + gamma * max(Q(s', a'))]
        self.Q[state][action] += self.alpha * (estimate - self.Q[state][action])

    def getPolicy(self, state):
        return self.computeActionFromQValues(state)

    def getValue(self, state):
        return self.computeValueFromQValues(state)


class PacmanQAgent(QLearningAgent):
    "Exactly the same as QLearningAgent, but with different default parameters"

    def __init__(self, epsilon=0.05,gamma=0.8,alpha=0.2, numTraining=0, **args):
        """
        These default parameters can be changed from the pacman.py command line.
        For example, to change the exploration rate, try:
            python pacman.py -p PacmanQLearningAgent -a epsilon=0.1
        alpha    - learning rate
        epsilon  - exploration rate
        gamma    - discount factor
        numTraining - number of training episodes, i.e. no learning after these many episodes
        """
        args['epsilon'] = epsilon
        args['gamma'] = gamma
        args['alpha'] = alpha
        args['numTraining'] = numTraining
        self.index = 0  # This is always Pacman
        QLearningAgent.__init__(self, **args)

    def getAction(self, state):
        """
        Simply calls the getAction method of QLearningAgent and then
        informs parent of action for Pacman.  Do not change or remove this
        method.
        """
        action = QLearningAgent.getAction(self,state)
        self.doAction(state,action)
        return action

class ApproximateQAgent(PacmanQAgent):
    """
       ApproximateQLearningAgent
       You should only have to overwrite getQValue
       and update.  All other QLearningAgent functions
       should work as is.
    """
    def __init__(self, extractor='IdentityExtractor', **args):
        self.featExtractor = util.lookup(extractor, globals())()
        PacmanQAgent.__init__(self, **args)
        self.weights = util.Counter()

    def getWeights(self):
        return self.weights

    def getQValue(self, state, action):
        """
          Should return Q(state,action) = w * featureVector
          where * is the dotProduct operator
        """
        "*** YOUR CODE HERE ***"
        # 直接回傳 w * featureVector
        return self.weights * self.featExtractor.getFeatures(state, action)

    def update(self, state, action, nextState, reward):
        """
           Should update your weights based on transition
        """
        "*** YOUR CODE HERE ***"
        # 令Q(s, a)估計值 大約等於 r + gamma * max(Q(s', a'))
        estimate = reward + self.discount * self.computeValueFromQValues(nextState)
        # difference = [r + gamma * max(Q(s', a'))] - Q(s, a)
        difference = estimate - self.getQValue(state, action)
        # 取得每個fi和wi
        features = self.featExtractor.getFeatures(state, action)
        weights = self.weights
        # wi = wi + alpha[difference]fi(s, a)
        for i in features:
            weights[i] += self.alpha * difference * features[i]


    def final(self, state):
        """Called at the end of each game."""
        # call the super-class final method
        PacmanQAgent.final(self, state)

        # did we finish training?
        if self.episodesSoFar == self.numTraining:
            # you might want to print your weights here for debugging
            "*** YOUR CODE HERE ***"
            pass
