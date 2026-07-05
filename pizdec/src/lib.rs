#![warn(clippy::pedantic)]
#![allow(dead_code)]

pub struct Solution;

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

    pub fn find_repeated_dna_sequences(s: String) -> Vec<String> {
        use std::collections::HashSet;
        if s.len() < 11 { return Vec::<String>::new() }

        let mut check = HashSet::<String>::new();
        let mut ans = HashSet::<String>::new();
        for i in 0..=(s.len()-10) {
            let curr = s[i..i+10].to_string();
            if !check.insert(curr.clone()) {
                ans.insert(curr.clone());
            }
        }

        return ans.into_iter().collect::<Vec<_>>();
    }

    pub fn can_jump(nums: Vec<i32>) -> bool {
        let n = nums.len();

        let mut max_idx = 0;

        for ( idx, val ) in nums.iter().enumerate() {
            // is curr cell further that max_reachable?
            if idx > max_idx { return false; }

            // max_reachable = either self or curr cell + its value
            max_idx = max_idx.max(idx + *val as usize);

            // is max_reach further or same as last cell?
            if (max_idx+1) >= n { return true; }
        }

        return false;
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::Solution;

    #[test]
    fn case1_55() {
        let nums = vec![2,3,1,1,4];
        assert_eq!(Solution::can_jump(nums), true);
    }

    #[test]
    fn case2_55() {
        let nums = vec![3,2,1,0,4];
        assert_eq!(Solution::can_jump(nums), false);
    }
    
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

    #[test]
    fn case1_187() {
        let s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT".to_string();
        let expected = HashSet::<String>::from_iter(vec!["AAAAACCCCC".to_string(),"CCCCCAAAAA".to_string()]);
        let ans = HashSet::from_iter(Solution::find_repeated_dna_sequences(s));
        assert_eq!(ans.symmetric_difference(&expected).count(), 0);
    }

    #[test]
    fn case2_187() {
        let s = "AAAAAAAAAAA".to_string();
        let expected = HashSet::<String>::from_iter(vec!["AAAAAAAAAA".to_string()]);
        let ans = HashSet::from_iter(Solution::find_repeated_dna_sequences(s));
        assert_eq!(ans.symmetric_difference(&expected).count(), 0);
    }
}
