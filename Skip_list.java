import java.util.*;
import java.io.*;

class Node<T extends Comparable<T>>
{
	T data;

	ArrayList<Node<T>> newNode = new ArrayList<>();

	private int height;	

	Node (int height)
	{
		// head node doesn't hold data so set to null
		data = null;

		this.newNode = new ArrayList<Node<T>>(height);

		for (int i = 0; i < height; i++)
		{
			newNode.add(null);
		}
	}

	Node (T data, int height)
	{

		this.data = data;
		this.newNode = new ArrayList<Node<T>>(height);

		for (int i = 0; i < height; i++)
		{
			this.newNode.add(null);
		}
	}

	public T value()
	{
		// return node's value.
		return this.data;
	}

	public int height()
	{
		// return node's height which will be it's size
		return newNode.size();
	}

	public Node<T> next(int level)
	{
		// check that level is within boundaries
		if (level < 0 || level > (height() - 1))
		{
			return null;
		}

		// return the node's level
		return newNode.get(level);
	}

	// Set the next reference at the given level within this node to node
	public void setNext(int level, Node<T> node)
	{
		
		newNode.set(level, node);

	}

	// skip list grows larger and more powerful with each node
	public void grow()
	{
		
		newNode.add(null);

	}

	// only grow powerful if we need to, 50% probability of doing so
	public boolean maybeGrow()
	{
		if (Math.random() >= 0.5)
		{
			grow();
			return true;
		}
		return false;
	}

	// called from trimSkipList function; trim a node's next references until that node's height matched the height param
	public void trim(int height)
	{
		newNode.remove(height);
	}
}

public class SkipList<T extends Comparable<T>>
{
	// disallow access to head and let size represent number of nodes in the skipList
	private Node<T> head;
	private int size = 0;

	// keep track of what level/height we are at
	public int height;

	SkipList() 
	{
		// if the head exists then give it height 1
		this.height = 1;
		this.head = new Node<T>(height);
	}

	SkipList(int height)
	{
		// increase height to 1 and give it the head node
		if (height == 0)
		{
			height = 1;
		}

		this.head = new Node<T>(height);

	}

	// returns the number of nodes in the skip list
	public int size()
	{
		return size;
	}

	// returns current height of the skip list, aka the height of the head node
	public int height()
	{
		return head.height();
	}

	public Node<T> head()
	{
		return head;
	}

	// generate a random height based using return from getMaxHeight and just send it to two parameter insert function
	public void insert(T data)
	{	
	
		insert(data, generateRandomHeight(getMaxHeight(size + 1)));

	}

	public void insert(T data, int height)
	{
		// have to increase size because insertion is occuring
		size++;

		// skip list must grow stronger to accomodate size increase
		growSkipList();

		// exclude head
		int currLevel = height()- 1;

		// new node to be inserted
		Node<T> node = new Node<T>(data, height);

		// traversal nodes
		Node<T> tmp = head();
		Node<T> nextRef = head().next(currLevel);

		// store a record of node references at each level
		LinkedList<Node<T>> ref = new LinkedList<>();
		
		// Go through each level and compare data to see where the node can be inserted
		while (currLevel >= 0)
		{
			// advance the pointer if we aren't at the tail of the skiplist
			while (nextRef != null && (node.value()).compareTo(nextRef.value()) == 1)
			{
				tmp = nextRef;
				nextRef = tmp.next(currLevel);

			}

			// boundary check
			if (currLevel <= height - 1)
			{
				// reconnect the next pointers
				node.setNext(currLevel, nextRef);
				tmp.setNext(currLevel, node);
			}

			// go down a level and update nextRef pointer to tmp's next at the new current level
			currLevel--;
			nextRef = tmp.next(currLevel);
		}
	}

	public void delete(T data)
	{
		int currLevel = (height() - 1);

		Node<T> tmp = head();
		Node<T> nextRef = head().next(currLevel);

		// save the references to and from the node to be deleted
		ArrayList<Node<T>> prevRightRef = new ArrayList<Node<T>>();
		ArrayList<Node<T>> prevLeftRef = new ArrayList<Node<T>>();

		// maintain record of deleted heights, if it occurs
		int heightRemoval = 0; 
		int i = currLevel;

		for (i = currLevel; i >= 0; i--)
		{
			if (i != currLevel)
			{
				nextRef = tmp.next(i);
			}

			// loop the refs 
			while(nextRef != null)
			{
			 	int isEqual = data.compareTo(nextRef.value());

			 	// value equal to data, keep going
				if (isEqual == 1)
				{
					tmp = nextRef;
					nextRef = nextRef.next(i);
				}
				else
				{
					break;
				}
			}

			// found the match
			if (nextRef != null && data.compareTo(nextRef.value()) == 0)
			{
				prevRightRef.add(0, tmp);
				prevLeftRef.add(0, nextRef.next(i));
			
				if (i == 0)
				{
					heightRemoval = nextRef.height();

					for (int j = 0; j < heightRemoval; j++)
						prevRightRef.get(j).setNext(j, prevLeftRef.get(j));

					size--;

					// need to trim skipList if height exceeds the max height for our current size
					while (height() > getMaxHeight(size))
					{
						trimSkipList();
					}
				}
			}
		}
	}

	public boolean contains(T data)
	{
		// exclude the head node
		int currLevel = height() - 1;

		// traversal nodes
		Node<T> tmp = head();
		Node<T> nextRef = head().next(currLevel);

		for (int i = currLevel; i >= 0; i--)
		{
			if (i != currLevel)
			{
				nextRef = tmp.next(i);
			}

			// loop the refs 
			while (nextRef != null)
			{
			 	int isEqual = data.compareTo(nextRef.value());

			 	// value equal to data, keep going
				if (isEqual == 1)
				{
					tmp = nextRef;
					nextRef = tmp.next(i);
				}

				// found the match
				else if (isEqual == 0)
				{
					return true;
				}

				// neither condition, break the loop
				else
				{
					break;
				}
			}
		}

		// data doesn't exist in the skip list
		return false;
	}

	public Node<T> get(T data)
	{
		// get our current height and then exclude the head node
		int currHeight = height();
		int currLevel = currHeight - 1;

		// traversal nodes
		Node<T> tmp = head();
		Node<T> nextRef = head().next(currLevel);

		while (currLevel >= 0)
		{
			if (nextRef == null || (nextRef.value()).compareTo(data) > 0)
			{
				// walk the list 
				tmp = nextRef;
				nextRef = tmp.next(currLevel);
			}

			else if ((nextRef.value()).compareTo(data) < 0)
			{
				// walk the list
				tmp = nextRef;
				nextRef = tmp.next(currLevel);

			} else {

				// the skip list only has the head node
				return tmp;

			}

			// advance nextRef to tmp's next at the current level
			nextRef = tmp.next(currLevel);
		}

		// value doesn't exist in skiplist
		return null;
	}

	// method that returns the max height of a skip list with n nodes
	
	private static int getMaxHeight(int n)
	{
		// if n is 2 then the max height possible can only be 1.
		if (n <= 2)
		{
			return 1;
		}

		return (int)Math.ceil((Math.log(n) / Math.log(2)));
		
	}

	// Returns 1 with 50% probability, 2 with 25% probability, 3 with 12.5% probability, without exceeding maxHeight
	
	private static int generateRandomHeight(int maxHeight)
	{
	
		int height = 1;
		
			while (height < maxHeight && Math.random() < 0.5 )
			{
				height++;
			}
		
		return height;
	}

	private void growSkipList()
	{
		int maxHeight = getMaxHeight(size);

		// max level size depends on skip list entries' heights - 1
		int maxSize = maxHeight - 1;

		// keep track of previous level size
		int prevMaxSize = height() - 1;

		// only want to grow if necessary
		if (maxHeight <= height())
		{
			return;
		}

		// traversal nodes
		Node<T> tmp = head();
		Node<T> currNode = head().next(prevMaxSize);

		// update head level to maintain max height.
		head().grow();

		while (currNode != null)
		{
			if (currNode.maybeGrow() ) 
			{
				// update references
				tmp.setNext(maxSize, currNode);
				tmp = currNode;

			} 

			currNode = currNode.next(prevMaxSize);
			
		}
	}

	// uses the same procedure as delete()
	private void trimSkipList()
	{
		int currHeight = height();
		int maxHeight = getMaxHeight(size);

		// boundary check
		if (height() <= maxHeight)
		{
			return;
		}

		// traversal nodes
		Node<T> currNode = head();
		Node<T> tmp = head();

		int prevLevel = height() - 1;

		while (currNode != null)
		{
			tmp = currNode.next(prevLevel);
			currNode.trim(prevLevel);
			currNode = tmp;
		}
	}

}
