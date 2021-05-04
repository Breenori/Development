package at.fhhagenberg.xml4.drugbank.domain;

import java.util.ArrayList;
import java.util.List;

public class TargetEntity {
	
	private String accession;
	private String name;
	private String organism;
	private List<DrugTarget> drugTargets = new ArrayList<DrugTarget>();

	public String getAccession() {
		return accession;
	}

	public void setAccession(String accession) {
		this.accession = accession;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getOrganism() {
		return organism;
	}

	public void setOrganism(String organism) {
		this.organism = organism;
	}

	public List<DrugTarget> getDrugTargets() {
		return drugTargets;
	}

	public void setDrugTargets(List<DrugTarget> drugTargets) {
		this.drugTargets = drugTargets;
	}

	public void addDrugTarget(DrugTarget drugTarget) {
		this.drugTargets.add(drugTarget);
	}

}
