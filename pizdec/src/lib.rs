#![warn(clippy::pedantic)]
#![allow(dead_code)]

struct Solution;

impl Solution {
    pub fn rob(nums: Vec<i32>) -> i32 {
        use std::cmp::max;
        let mut prev1:i32 = 0;
        let mut prev2:i32 = 0;
        
        nums.iter().for_each(|i| {
            let curr = max(prev2+i, prev1);
            prev2 = prev1;
            prev1 = curr;
        }); 
        
        return prev1;
    }

    pub fn find_all_recipes(recipes: Vec<String>, ingredients: Vec<Vec<String>>, supplies: Vec<String>) -> Vec<String> {
        use std::collections::{HashSet, HashMap};
        
        let mut ans = Vec::<String>::new();
        let mut available = HashSet::new();
        let mut counter = HashMap::new();
        let mut reqs = HashMap::<&String, Vec<&String>>::new();

        for item in supplies.iter() {
            available.insert(item);
        }

        let mut q = Vec::<&String>::new();

        // step 1 -> init queue and reqs and counter
        for i in 0..recipes.len() {
            let rec = recipes.get(i).unwrap();
            counter.insert(rec, ingredients[i].len());
            for ing in ingredients[i].iter() {
                reqs.entry(ing).and_modify(|v| v.push(rec)).or_insert(vec![rec]);

                if available.contains(ing) {
                    counter.entry(rec).and_modify(|cnt| {
                        *cnt-=1;
                        if *cnt==0 {q.push(rec);}
                    });
                }
            }
        }
    
        // step 2 -> reach empty queue
        while let Some(curr) = q.pop() {
            ans.push(curr.to_string());
            if let Some(waiting) = reqs.get(curr) {
                for i in waiting {
                    counter.entry(i).and_modify(|cnt| {
                        *cnt-=1;
                        if *cnt==0 {q.push(i);}
                    });
                }
            }
        }

        return ans;
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::Solution;
    
    #[test]
    fn case1_198() {
        let nums = vec![1,2,3,1];
        assert_eq!(Solution::rob(nums), 4);
    }

    #[test]
    fn case2_198() {
        let nums = vec![2,7,9,3,1];
        assert_eq!(Solution::rob(nums), 12);
    }

    #[test]
    fn case1_2115() {
        let recipes = vec!["bread".to_string()];
        let ingredients = vec![vec!["yeast".to_string(), "flour".to_string()]];
        let supplies = vec!["yeast".to_string(), "corn".to_string(), "flour".to_string()];
        let expected = HashSet::<String>::from_iter(vec!["bread".to_string()]);
        let ans = HashSet::from_iter(Solution::find_all_recipes(recipes, ingredients, supplies));
        assert_eq!(ans.symmetric_difference(&expected).count(), 0);
    }
    
    #[test]
    fn case2_2115() {
        let recipes = vec!["sandwich".to_string(), "bread".to_string()];
        let ingredients = vec![vec!["meat".to_string(), "bread".to_string()], vec!["yeast".to_string(), "flour".to_string()]];
        let supplies = vec!["yeast".to_string(), "meat".to_string(), "flour".to_string()];
        let expected = HashSet::<String>::from_iter(recipes.clone());
        let ans = HashSet::from_iter(Solution::find_all_recipes(recipes, ingredients, supplies));
        assert_eq!(ans.symmetric_difference(&expected).count(), 0);
    }

    #[test]
    fn case3_2115() {
        let recipes = vec!["sandwich".to_string(), "burger".to_string(), "bread".to_string()];
        let ingredients = vec![
            vec!["meat".to_string(), "bread".to_string()], 
            vec!["sandwich".to_string(), "bread".to_string(), "meat".to_string()],
            vec!["yeast".to_string(), "flour".to_string()]
        ];
        let supplies = vec!["yeast".to_string(), "meat".to_string(), "flour".to_string()];
        let expected = HashSet::<String>::from_iter(recipes.clone());
        let ans = HashSet::from_iter(Solution::find_all_recipes(recipes, ingredients, supplies));
        assert_eq!(ans.symmetric_difference(&expected).count(), 0);
    }
}
