package at.fhhagenberg.xml4.drugbank.domain;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Drug {
	
	private String accession;
	private Set<String> secondaryAccessions = new HashSet<String>();
	private String name;
	private Set<String> atcCodes = new HashSet<String>();
	private List<Group> groups = new ArrayList<>();
	private Type type;
	private String description;
	private String indication;
	private Set<String> synonyms = new HashSet<String>();
	private Set<Product> prescriptionProducts = new HashSet<Product>();
	private Set<Product> overTheCounterProducts = new HashSet<Product>();
	private List<DrugTarget> targets = new ArrayList<DrugTarget>();
	

	public String getAccession() {
		return accession;
	}

	public void setAccession(String accession) {
		this.accession = accession;
	}

	public Set<String> getSecondaryAccessions() {
		return secondaryAccessions;
	}

	public void setSecondaryAccessions(Set<String> secondaryAccessions) {
		this.secondaryAccessions = secondaryAccessions;
	}

	public void addSecondaryAccessions(String secondaryAccession) {
		secondaryAccessions.add(secondaryAccession);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Set<String> getAtcCodes() {
		return atcCodes;
	}

	public void setAtcCodes(Set<String> atcCodes) {
		this.atcCodes = atcCodes;
	}

	public void addAtcCode(String atcCode) {
		atcCodes.add(atcCode);
	}

	public List<Group> getGroups() {
		return groups;
	}

	public void setGroups(List<Group> groups) {
		this.groups = groups;
	}

	public void addGroup(Group group) {
		this.groups.add(group);
	}

	public void setGroup(Group group) {
		groups.add(group);
	}

	public Type getType() {
		return type;
	}

	public void setType(Type type) {
		this.type = type;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getIndication() {
		return indication;
	}

	public void setIndication(String indication) {
		this.indication = indication;
	}

	public Set<String> getSynonyms() {
		return synonyms;
	}

	public void setSynonyms(Set<String> synonyms) {
		this.synonyms = synonyms;
	}
	
	public void addSynonym(String synoym){
		this.synonyms.add(synoym);
	}

	public Set<Product> getPrescriptionProducts() {
		return prescriptionProducts;
	}

	public void setPrescriptionProducts(Set<Product> prescriptionProducts) {
		this.prescriptionProducts = prescriptionProducts;
	}
	
	public void addPrescriptionProduct(Product prescriptionProduct) {
		prescriptionProducts.add(prescriptionProduct);
	}

	public Set<Product> getOverTheCounterProducts() {
		return overTheCounterProducts;
	}

	public void setOverTheCounterProducts(Set<Product> overTheCounterProducts) {
		this.overTheCounterProducts = overTheCounterProducts;
	}
	
	public void addOverTheCounterProduct(Product overTheCounterProduct) {
		overTheCounterProducts.add(overTheCounterProduct);
	}

	public List<DrugTarget> getTargets() {
		return targets;
	}

	public void setTargets(List<DrugTarget> targets) {
		this.targets = targets;
	}
	
	public void addDrugTarget(DrugTarget target){
		this.targets.add(target);
	}

}
